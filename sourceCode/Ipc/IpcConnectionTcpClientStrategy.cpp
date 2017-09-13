#include "IpcConnectionTcpClientStrategy.h"
#include "IIpcConnectionReceiver.h"
#include "ITcpClient.h"
#include "IIpcMessage.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "ITimer.h"
#include "LoopMain.h"
#include "Trace.h"
#include "App.h"

namespace Ipc {

IpcConnectionTcpClientStrategy::IpcConnectionTcpClientStrategy(
                                                   std::shared_ptr<IIpcConnectionReceiver> connectionReceiver,
                                                   IpcMessageFactroyMap ipcMessageFactories,
                                                   std::shared_ptr<Network::ITcpClient> client)
: connectionReceiver_(connectionReceiver)
, ipcMessageFactories_(ipcMessageFactories)
, client_(client)
{
    if (!client_)
    {
        TRACE_ERROR("null Ipc client");
        throw std::invalid_argument("null Ipc client!");
    }
    client_->init();
}

IpcConnectionTcpClientStrategy::IpcConnectionTcpClientStrategy(
                                                   std::shared_ptr<Network::ITcpClient> client)
    : client_(client)
{
    if (!client_)
    {
        TRACE_ERROR("null Ipc client");
        throw std::invalid_argument("null Ipc client!");
    }
    client_->init();
}

IpcConnectionTcpClientStrategy::~IpcConnectionTcpClientStrategy()
{
}

void IpcConnectionTcpClientStrategy::connect()
{
    TRACE_ENTER();
    client_->connect();
}

void IpcConnectionTcpClientStrategy::send(IpcMessage::IIpcMessage& msg)
{
    TRACE_ENTER();
    if (!msg.getSource().isValid())
    {
        msg.setSource(client_->getLocalEndpoint());
    }

    if (!msg.getDestnation().isValid())
    {
        msg.setDestnation(client_->getRemoteEndpoint());
    }

    Serialize::WriteBuffer writeBuffer;
    msg.serialize(writeBuffer);
    TRACE_NOTICE("send msg:" << writeBuffer);
    client_->send(writeBuffer);
    heartbeartTimer_->resetTimer();
}

void IpcConnectionTcpClientStrategy::disconnect()
{
    TRACE_ENTER();
    client_->disconnect();
    client_->cleanup();
    client_->restart();
}

void IpcConnectionTcpClientStrategy::setIpcConnectionReceiver(std::shared_ptr<IIpcConnectionReceiver> receiver)
{
    TRACE_ENTER();
    connectionReceiver_ = receiver;
}

void IpcConnectionTcpClientStrategy::addIpcMessageFactory(std::shared_ptr<IpcMessage::IIpcMessageFactory> factory)
{
    ipcMessageFactories_[factory->messageType()] = factory;
}

void IpcConnectionTcpClientStrategy::setHeartbeatTimer(std::shared_ptr<TimerHandler::ITimer> timer)
{
    heartbeartTimer_ = timer;
}

void IpcConnectionTcpClientStrategy::setConnectionTimer(std::shared_ptr<TimerHandler::ITimer> timer)
{
    connectionTimer_ = timer;
}


void IpcConnectionTcpClientStrategy::onConnect()
{
    TRACE_ENTER();
    connectionReceiver_->onConnect();
    if (connectionTimer_)
    {
        connectionTimer_->resetTimer();
        Core::LoopMain::instance().registerTimer(connectionTimer_.get());
    }

    if (heartbeartTimer_)
    {
        heartbeartTimer_->resetTimer();
        Core::LoopMain::instance().registerTimer(heartbeartTimer_.get());
    }
}

void IpcConnectionTcpClientStrategy::onReceive(Serialize::ReadBuffer& readBuffer)
{
    while (!readBuffer.isEndOfData())
    {
        uint8_t messageType = static_cast<uint8_t>(IpcMessage::IpcMessage_None);
        readBuffer.peek(messageType);
        TRACE_DEBUG("Receive ipc message: message type = "
                    << IpcMessage::IpcMessageTypeString(static_cast<IpcMessage::IpcMessageType>(messageType))
                    << ", message stream:" << readBuffer);

        IpcMessageFactroyMap::iterator
                it = ipcMessageFactories_.find(static_cast<IpcMessage::IpcMessageType>(messageType));
        if (it != ipcMessageFactories_.end())
        {
            std::shared_ptr<IpcMessage::IIpcMessageFactory>& factory = it->second;
            IpcMessage::IpcMessageApplicationIntType ipcApplicationType = 0xff;
            readBuffer.peek(ipcApplicationType, sizeof(messageType));
            std::unique_ptr<IpcMessage::IIpcMessage> msg(factory->createMessage(ipcApplicationType));
            if (msg)
            {
                msg->unserialize(readBuffer);
                TRACE_DEBUG("Receive ipc msg:" << *msg);
                if (shouldForwardToApplication(static_cast<IpcMessage::IpcMessageType>(messageType),
                                               ipcApplicationType))
                {
                    connectionReceiver_->onReceive(std::move(msg));
                }
            }
            else
            {
                TRACE_WARNING("Recieve error message, wrong application type = "
                              << static_cast<int>(ipcApplicationType)
                              << ", for ipc type = "
                              << static_cast<int>(messageType));
            }
        }
        else
        {
            TRACE_WARNING("Recieve error message, wrong ipc message type = "
                          << static_cast<int>(messageType));
            break;
        }
    }
    connectionTimer_->resetTimer();
}

void IpcConnectionTcpClientStrategy::onDisconnect()
{
    TRACE_ENTER();
    if (connectionTimer_)
    {
        Core::LoopMain::instance().deRegisterTimer(connectionTimer_->getTimerId());
    }

    if (heartbeartTimer_)
    {
        Core::LoopMain::instance().deRegisterTimer(heartbeartTimer_->getTimerId());
    }
    connectionReceiver_->onDisconnect();
}

bool IpcConnectionTcpClientStrategy::shouldForwardToApplication(IpcMessage::IpcMessageType msgType,
                                                  IpcMessage::IpcMessageApplicationIntType appType)
{
    static_cast<void>(appType);
    return !(msgType == IpcMessage::IpcMessage_IpcCommunication);
}

}
