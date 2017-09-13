#ifndef IPCCONNECTIONTCPSERVERSTRATEGY_H
#define IPCCONNECTIONTCPSERVERSTRATEGY_H
#include "IIpcConnectionServerStrategy.h"
#include "ITcpConnectionAcceptor.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace Network {
class ITcpServer;
}

namespace Ipc {
class IIpcConnectionAcceptor;

class IpcConnectionTcpServerStrategy : public IIpcConnectionServerStrategy,
                                       public Network::ITcpConnectionAcceptor
{
    std::shared_ptr<IIpcConnectionAcceptor> connectionAcceptor_;
    std::shared_ptr<Network::ITcpServer> server_;
public:
    IpcConnectionTcpServerStrategy(std::shared_ptr<IIpcConnectionAcceptor> connectionAcceptor,
                                   std::shared_ptr<Network::ITcpServer> server);
    IpcConnectionTcpServerStrategy(std::shared_ptr<Network::ITcpServer> server);
    ~IpcConnectionTcpServerStrategy();

    virtual void startup();
    virtual void shutdown();
    virtual void onAccept(int fd,
                          const Network::IpSocketEndpoint& localEndPoint,
                          const Network::IpSocketEndpoint& remoteEndPoint);
    virtual void setIpcConnectionAcceptor(std::shared_ptr<IIpcConnectionAcceptor> acceptor);

public:
     GETCLASSNAME(IpcConnectionTcpServerStrategy)
};

}
#endif // IPCCONNECTIONTCPSERVERSTRATEGY_H
