#include "IpcClientCreator.h"
#include "IpcClient.h"
#include "IpcConnectionTcpClientStrategy.h"
#include "IpcConnectionTimer.h"
#include "IpcHeartbeatTimer.h"
#include "TcpClient.h"
#include "TcpSocket.h"
#include "IpSocketEndpoint.h"
#include "LoopMain.h"

namespace Ipc {
IpcClientCreator::IpcClientCreator()
{
}

IIpcClient* IpcClientCreator::CreateWithTcpClientStrategy(const Network::IpSocketEndpoint& localEndpoint,
                                                          const Network::IpSocketEndpoint& remoteEndpoint,
                                                          std::shared_ptr<IIpcConnectionReceiver> receiver,
                                                          IpcMessageFactories factories)
{
    // Tcp client
    Network::TcpClient* tcpClientPtr = new Network::TcpClient(localEndpoint, remoteEndpoint);
    std::shared_ptr<Network::ITcpClient> tcpClient(tcpClientPtr);

    return CreateWithTcpClient(tcpClient, receiver, factories);
}

IIpcClient* IpcClientCreator::CreateWithTcpClientStrategy(int fd,
                                               const Network::IpSocketEndpoint& localEndPoint,
                                               const Network::IpSocketEndpoint& remoteEndPoint,
                                               std::shared_ptr<IIpcConnectionReceiver> receiver,
                                               IpcMessageFactories factories)
{
    std::shared_ptr<Network::TcpSocket> socket(new Network::TcpSocket(fd, localEndPoint, remoteEndPoint));

    // Tcp client
    Network::TcpClient* tcpClientPtr = new Network::TcpClient(socket, Network::TcpState::Tcp_Established);
    std::shared_ptr<Network::ITcpClient> tcpClient(tcpClientPtr);
    Core::LoopMain::instance().registerIo(Io::IoFdType::IoFdRead, tcpClientPtr);
    return CreateWithTcpClient(tcpClient, receiver, factories, true);
}

IIpcClient* IpcClientCreator::CreateWithTcpClient(std::shared_ptr<Network::ITcpClient> tcpClient,
                                       std::shared_ptr<IIpcConnectionReceiver> receiver,
                                       IpcMessageFactories factories,
                                       bool isAcceptedClient)
{
    // Ipc client strategy
    Ipc::IpcConnectionTcpClientStrategy* ipcConnectionClientStrategyPtr =
            new Ipc::IpcConnectionTcpClientStrategy(tcpClient);
    std::shared_ptr<Ipc::IpcConnectionTcpClientStrategy> ipcConnectionClientStrategy(ipcConnectionClientStrategyPtr);

    // Ipc client
    Ipc::IpcClient* ipcClientPtr = new Ipc::IpcClient(ipcConnectionClientStrategy);

    // tcp connection receiver
    tcpClient->setConnectionReceiver(ipcConnectionClientStrategy);

    // Set ipcConnectionTcpStrategy
    Ipc::IIpcConnectionClientStrategy* strategy = static_cast<Ipc::IIpcConnectionClientStrategy*>(ipcConnectionClientStrategyPtr);

    strategy->setIpcConnectionReceiver(receiver);

    for (IpcMessageFactories::iterator it = factories.begin(); it != factories.end(); ++it)
    {
        strategy->addIpcMessageFactory(*it);
    }

    std::shared_ptr<TimerHandler::ITimer>
            connectionTimer(new IpcConnectionTimer(strategy, receiver.get()));
    std::shared_ptr<TimerHandler::ITimer>
            heartbeatTimer(new IpcHeartbeatTimer(strategy));
    strategy->setConnectionTimer(connectionTimer);
    strategy->setHeartbeatTimer(heartbeatTimer);

    if (isAcceptedClient)
    {
        Network::ITcpConnectionReceiver* tcpConnectionReceiver = ipcConnectionClientStrategyPtr;
        tcpConnectionReceiver->onConnect();
    }

    return ipcClientPtr;
}

}
