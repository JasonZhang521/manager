#ifndef IPCCLIENTCREATOR_H
#define IPCCLIENTCREATOR_H
#include <memory>
#include <vector>
namespace Network {
class IpSocketEndpoint;
class ITcpClient;
}

namespace IpcMessage {
class IIpcMessageFactory;
}

using IpcMessageFactories = std::vector<std::shared_ptr<IpcMessage::IIpcMessageFactory> >;
namespace Ipc {
class IIpcClient;
class IIpcConnectionReceiver;

class IpcClientCreator
{
public:
    IpcClientCreator();
    static IIpcClient* CreateWithTcpClientStrategy(const Network::IpSocketEndpoint& localEndPoint,
                                                   const Network::IpSocketEndpoint& remoteEndPoint,
                                                   std::shared_ptr<IIpcConnectionReceiver> receiver,
                                                   IpcMessageFactories factories);
    static IIpcClient* CreateWithTcpClientStrategy(int fd,
                                                   const Network::IpSocketEndpoint& localEndPoint,
                                                   const Network::IpSocketEndpoint& remoteEndPoint,
                                                   std::shared_ptr<IIpcConnectionReceiver> receiver,
                                                   IpcMessageFactories factories);

private:
    static IIpcClient* CreateWithTcpClient(std::shared_ptr<Network::ITcpClient> tcpClient,
                                           std::shared_ptr<IIpcConnectionReceiver> receiver,
                                           IpcMessageFactories factories,
                                           bool isAcceptedClient = false);
};
}

#endif // IPCCLIENTCREATOR_H
