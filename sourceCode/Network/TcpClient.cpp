#include "TcpClient.h"
#include "TcpSocket.h"
#include "ITcpConnectionReceiver.h"
#include "IpSocketEndpoint.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "EventIdGenerator.h"
#include "LoopMain.h"
#include "Trace.h"
#include "App.h"
#include "AppConst.h"

namespace Network {


TcpClient::ConnectionTimer::ConnectionTimer(ITcpClient* client)
    : TimerHandler::ITimer(ConnectionTimeout)
    , client_(client)
{
    if (client == nullptr)
    {
        throw std::invalid_argument("nullptr for tcp client!");
    }
}

TcpClient::ConnectionTimer::~ConnectionTimer()
{
}

void TcpClient::ConnectionTimer::onTime()
{
    TRACE_WARNING("Tcp client connect to server timeout, " << " client:" << *dynamic_cast<TcpClient*>(client_)->socket_);
    client_->disconnect();
    client_->restart();
}

std::ostream& TcpClient::ConnectionTimer::operator<<(std::ostream& os)
{
    os << "[";
    TimerHandler::ITimer::print(os);
    os << ", tcpClient=" << client_
       << "]";
    return os;
}

TcpClient::OutBuffer::OutBuffer()
    : buffer_(new char[DefaultBufferSize])
    , bufferSize_(DefaultBufferSize)
    , pos_(0)
    , dataSize_(0)
{
}

TcpClient::OutBuffer::~OutBuffer()
{
    delete [] buffer_;
}

void TcpClient::OutBuffer::append(const void* buf, unsigned int len)
{
    const char* buffer = reinterpret_cast<const char*>(buf);
    if (bufferSize_ - dataSize_ >= len)
    {
        std::copy(buffer, buffer + len, buffer_ + pos_);
        dataSize_ += len;
    }
    else
    {
        std::copy(buffer_ + pos_, buffer_ + dataSize_, buffer_);
        dataSize_ -= pos_;
        pos_ = 0;
        std::copy(buffer, buffer + len, buffer_);
        dataSize_ += len;
    }
}

char* TcpClient::OutBuffer::getUnwrittenBuffer()
{
    return buffer_ + pos_;
}

unsigned TcpClient::OutBuffer::getUnwrittenSize() const
{
    return dataSize_ - pos_;
}

void TcpClient::OutBuffer::resetPos(unsigned int outSize)
{
    pos_ += outSize;
}


TcpClient::TcpClient(const IpSocketEndpoint& localEndpoint,
                     const IpSocketEndpoint& remoteEndpoint,
                     std::shared_ptr<ITcpConnectionReceiver> receiver)
    :state_(TcpState::Tcp_Closed)
    ,socket_(new TcpSocket(localEndpoint, remoteEndpoint))
    ,tcpConnectionReceiver_(receiver)
{
    if (!receiver)
    {
        TRACE_ERROR("Initial Tcp Client with null connection connection receiver, local = " << localEndpoint << ", remote = " << remoteEndpoint);
        throw std::invalid_argument("Initial Tcp Client with null connection connection receiver");
    }
}

TcpClient::TcpClient(const IpSocketEndpoint& localEndpoint, const IpSocketEndpoint& remoteEndpoint)
    :state_(TcpState::Tcp_Closed)
    ,socket_(new TcpSocket(localEndpoint, remoteEndpoint))
{

}

TcpClient::TcpClient(std::shared_ptr<TcpSocket> socket, TcpState state)
    :state_(state)
    ,socket_(socket)
{
}

TcpClient::~TcpClient()
{
    Core::LoopMain::instance().deRegisterIo(Io::IoFdType::IoFdAll, getIoHandle());
}

TcpResult TcpClient::init()
{
    TRACE_ENTER();
    if (SOCKET_SUCCESS == socket_->init())
    {
       return TcpResult::Success;
    }
    else
    {
        TRACE_WARNING("Tcp client init failed! error infomation:" << socket_->getErrorInfo());
        return TcpResult::Failed;
    }
}

TcpResult TcpClient::bind()
{
    TRACE_ENTER();
    if (SOCKET_SUCCESS == socket_->bind())
    {
       TRACE_NOTICE("tcp client bind successfully! bind to:" << socket_->getLocalEndpoint());
       return TcpResult::Success;
    }
    else
    {
        TRACE_NOTICE("tcp client bind error! bind to:" << socket_->getLocalEndpoint() << ", error info:" << socket_->getErrorInfo());
        return TcpResult::Failed;
    }
}

TcpResult TcpClient::connect()
{
    TRACE_DEBUG("localEndpoint:" << socket_->getLocalEndpoint() << ", remoteEndpoint:" << socket_->getRemoteEndpoint());
    if (!connectionTimer_)
    {
        connectionTimer_ = std::shared_ptr<ConnectionTimer>(new ConnectionTimer(this));
    }
    // connect
    int ret = socket_->connect();

    if (SOCKET_ERROR == ret)
    {
        int errorNo = socket_->getErrorNo();
        if (SOCKET_EINPROGRESS == errorNo || SOCKET_EAGAIN == errorNo)
        {
            TRACE_NOTICE(socket_->getErrorInfo() << " socket = " << *socket_);
            state_ = TcpState::Tcp_Connecting;
            connectionTimer_->resetTimer();
            Core::LoopMain::instance().registerTimer(connectionTimer_.get());
            Core::LoopMain::instance().registerIo(Io::IoFdType::IoFdWrite, this);
            return TcpResult::Success;    
        }    
        else
        {
            TRACE_WARNING(socket_->getErrorInfo() << ", socket = " << *socket_);
            connectionTimer_->resetTimer();
            Core::LoopMain::instance().registerTimer(connectionTimer_.get());
            return TcpResult::Failed;
        }
    }
    else
    {
        TRACE_NOTICE("client connect to server successfully, socket = " << *socket_);

        // register the IO
        Io::IIoEvent* ioEvent = this;
        Core::LoopMain::instance().registerIo(Io::IoFdType::IoFdRead, ioEvent);
        Core::LoopMain::instance().deRegisterTimer(connectionTimer_->getTimerId());

        state_ = TcpState::Tcp_Established;
        tcpConnectionReceiver_->onConnect();
        return TcpResult::Success;
    }
}

TcpResult TcpClient::send(const Serialize::WriteBuffer& buffer)
{
    TRACE_ENTER();
    outBuffer_.append(buffer.getBuffer(), buffer.getDataSize());
    int sendBytes = socket_->send(outBuffer_.getUnwrittenBuffer(), outBuffer_.getUnwrittenSize(), SOCKET_FLAG_NONE);
    if (SOCKET_ERROR == sendBytes)
    {
        TRACE_WARNING("send message error: error information = " << socket_->getErrorInfo());
        disconnect();
        restart();
        return TcpResult::Failed;
    }
    else if (static_cast<unsigned int>(sendBytes) != outBuffer_.getUnwrittenSize())
    {
        TRACE_NOTICE("send message fragmantation! plan send:" << outBuffer_.getUnwrittenSize() << ", actuall send:" << sendBytes);
        outBuffer_.resetPos(sendBytes);
        return TcpResult::Success;
    }
    else
    {
        outBuffer_.resetPos(sendBytes);
        return TcpResult::Success;
    }
}

TcpResult TcpClient::receive()
{
    TRACE_ENTER();
    Serialize::ReadBuffer readBuffer;
    int numOfBytesReceived = socket_->recv(reinterpret_cast<SocketDataBuffer>(readBuffer.getBuffer()), readBuffer.getBufferSize(), SOCKET_FLAG_NONE);
    if (SOCKET_ERROR == numOfBytesReceived)
    {
        TRACE_WARNING("receive error, error info = " << socket_->getErrorInfo());
        disconnect();
        restart();
        return TcpResult::Failed;
    }
	else if (0 == numOfBytesReceived)
	{
        TRACE_NOTICE("Tcp remote end is disconnected! try to re-connect");
        disconnect();
        restart();
        return TcpResult::Failed;
	}
    else
    {
        readBuffer.setDataSize(numOfBytesReceived);
        tcpConnectionReceiver_->onReceive(readBuffer);
        return TcpResult::Success;
    }
}

TcpResult TcpClient::disconnect()
{
    TRACE_ENTER();
    TRACE_NOTICE("TcpClient::disconnect");
    // deregister the IO
    Core::LoopMain::instance().deRegisterIo(Io::IoFdType::IoFdAll, getIoHandle());

    state_ = TcpState::Tcp_Closed;
    TcpResult ret = TcpResult::Success;
    if (SOCKET_ERROR == socket_->close())
    {
        TRACE_NOTICE(socket_->getErrorInfo());
        ret = TcpResult::Failed;
    }
    tcpConnectionReceiver_->onDisconnect();
    return ret;
}

TcpResult TcpClient::cleanup()
{
    TRACE_ENTER();
    if (SOCKET_ERROR == socket_->shutdown(SOCKET_SD_BOTH))
    {
        TRACE_NOTICE(socket_->getErrorInfo());
        return TcpResult::Failed;
    }
    else
    {
        return TcpResult::Success;
    }
}

TcpResult TcpClient::restart()
{
    TRACE_ENTER();
    socket_ = std::shared_ptr<TcpSocket>(new TcpSocket(socket_->getRemoteEndpoint(), socket_->getRemoteEndpoint()));
    init();
    return TcpResult::Success;
}

void TcpClient::run(EventHandler::EventFlag flag)
{
    TRACE_ENTER();
    if (state_ == TcpState::Tcp_Established)
    {
        if (flag == EventHandler::EventFlag::Event_IoRead)
        {
            receive();
        }
    }
    else if (state_ == TcpState::Tcp_Connecting)
    {
        if (flag == EventHandler::EventFlag::Event_IoWrite)
        {
            TRACE_NOTICE("client connect to server successfully, socket = " << *socket_);
            // register the IO
            Io::IIoEvent* ioEvent = this;
            Core::LoopMain::instance().registerIo(Io::IoFdType::IoFdRead, ioEvent);

            state_ = TcpState::Tcp_Established;
            Core::LoopMain::instance().deRegisterIo(Io::IoFdType::IoFdWrite, getIoHandle());
            Core::LoopMain::instance().deRegisterTimer(connectionTimer_->getTimerId());
            tcpConnectionReceiver_->onConnect();
        }
    }
}

std::ostream& TcpClient::operator<< (std::ostream& os) const
{
    os << "["
       << "Tcpclient: state=" << toString(state_)
       << ", socket=" << *socket_
       << "]";

    return os;
}

int TcpClient::getIoHandle()
{
    TRACE_ENTER();
    return socket_->getFd();
}

IpSocketEndpoint TcpClient::getRemoteEndpoint() const
{
    SocketAddress addr;
    SocketAddresstLength len = sizeof(SocketAddress);
    socket_->getPeerName(&addr, len);
    return IpSocketEndpoint(addr);
}

IpSocketEndpoint TcpClient::getLocalEndpoint() const
{
    SocketAddress addr;
    SocketAddresstLength len = sizeof(SocketAddress);
    socket_->getSockName(&addr, len);
    return IpSocketEndpoint(addr);
}

void TcpClient::setConnectionReceiver(std::shared_ptr<ITcpConnectionReceiver> receiver)
{
    TRACE_ENTER();
    tcpConnectionReceiver_ = receiver;
}


}
