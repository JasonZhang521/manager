#ifndef IPCSERVERCREATOR_H
#define IPCSERVERCREATOR_H
#include <memory>

namespace Network {
class IpSocketEndpoint;
}

namespace Ipc {
class IIpcConnectionAcceptor;
class IIpcServer;
class IpcServerCreator
{
public:
    IpcServerCreator();

    static IIpcServer* CreateWithTcpServer(const Network::IpSocketEndpoint& localEndPoint,
                                           std::shared_ptr<Ipc::IIpcConnectionAcceptor> ipcConnectionAcceptor);
};
}
#endif // IPCSERVERCREATOR_H
