#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "ITcpServer.h"
#include "ITcpClient.h"
#include "ITcpConnectionAcceptor.h"
#include "IIoEvent.h"
#include "TcpSocket.h"
#include "TcpState.h"
#include "Component.h"
#include "Macro.h"
#include <vector>

namespace Network {

class TcpServer : public ITcpServer, public Io::IIoEvent
{
    TcpSocket socket_;
    TcpState state_;
    std::shared_ptr<ITcpConnectionAcceptor> tcpConnectionAcceptor_;
public:
    TcpServer(const IpSocketEndpoint& localEndpoint);
    TcpServer(const IpSocketEndpoint& localEndpoint, std::shared_ptr<ITcpConnectionAcceptor> acceptor);
    virtual ~TcpServer();
private:
    virtual TcpResult init();
    virtual TcpResult bind();
    virtual TcpResult listen(int backlog);
    virtual TcpResult accept(int flag);
    virtual TcpResult disconnect();
    virtual TcpResult cleanup();
    virtual void setConnectionAcceptor(std::shared_ptr<ITcpConnectionAcceptor> acceptor);
    virtual void run(EventHandler::EventFlag flag = EventHandler::EventFlag::Event_NoFlag);
    virtual std::ostream& operator<< (std::ostream& os) const;
    virtual int getIoHandle();

public:
     GETCLASSNAME(TcpServer)
};

}

#endif // TCPSERVER_H
