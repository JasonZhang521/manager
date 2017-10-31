#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include "ITcpClient.h"
#include "IIoEvent.h"
#include "ITimer.h"
#include "TcpState.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace Serialize {
class WriteBuffer;
}

namespace Network {

class TcpSocket;

class TcpClient : public ITcpClient, public Io::IIoEvent
{
    struct ConnectionTimer : public TimerHandler::ITimer
    {
        ConnectionTimer(ITcpClient* client);
        ~ConnectionTimer();
        virtual void onTime();
        virtual std::ostream& operator<<(std::ostream& os);
    private:
        ITcpClient* client_;
    public:
        GETCLASSNAME(ConnectionTimer)
    };

    class OutBuffer
    {
        char* buffer_;
        unsigned int bufferSize_;
        unsigned int pos_;
        unsigned int dataSize_;
        const static unsigned int DefaultBufferSize = 128 * 1024;
    public:
        OutBuffer();
        ~OutBuffer();
        void append(const void* buf, unsigned int len);
        char* getUnwrittenBuffer();
        unsigned getUnwrittenSize() const;
        void resetPos(unsigned int outSize);
    };

    TcpState state_;
    std::shared_ptr<TcpSocket> socket_;
    std::shared_ptr<ITcpConnectionReceiver> tcpConnectionReceiver_;
    std::shared_ptr<ConnectionTimer> connectionTimer_;
    OutBuffer outBuffer_;
public:
    TcpClient(const IpSocketEndpoint& localEndpoint,
              const IpSocketEndpoint& remoteEndpoint,
              std::shared_ptr<ITcpConnectionReceiver> receiver);
    TcpClient(const IpSocketEndpoint& localEndpoint, const IpSocketEndpoint& remoteEndpoint);
    TcpClient(std::shared_ptr<TcpSocket> socket, TcpState state);
    virtual ~TcpClient();
private:
    virtual TcpResult init();
    virtual TcpResult bind();
    virtual TcpResult connect();
    virtual TcpResult send(const Serialize::WriteBuffer&);
    virtual TcpResult receive();
    virtual TcpResult disconnect();
    virtual TcpResult cleanup();
    virtual TcpResult restart();
    virtual void setConnectionReceiver(std::shared_ptr<ITcpConnectionReceiver> receiver);

    virtual void run(EventHandler::EventFlag flag = EventHandler::EventFlag::Event_NoFlag);
    virtual std::ostream& operator<< (std::ostream& os) const;
    virtual int getIoHandle();

    virtual IpSocketEndpoint getRemoteEndpoint() const;
    virtual IpSocketEndpoint getLocalEndpoint() const;

public:
     GETCLASSNAME(TcpClient)
};

}

#endif // TCPCLIENT_H
