#include "ClusterMgtConnectionAcceptor.h"
#include "ClusterMgtConnectionReceiver.h"
#include "IClusterMgtClientsManagement.h"
#include "IpcConnectionTcpClientStrategy.h"
#include "IpcClientCreator.h"
#include "IClusterMgtController.h"
#include "IpcClient.h"
#include "TcpSocket.h"
#include "TcpClient.h"
#include "SystemMonitorMessageFactory.h"
#include "IpcLayerMessageFactory.h"
#include "LoopMain.h"
#include "Trace.h"

namespace ClusterManagement {
ClusterMgtConnectionAcceptor::ClusterMgtConnectionAcceptor(ClientType type, std::shared_ptr<IClusterMgtController> clusterMgtController)
    :clientType_(type)
    ,clusterMgtController_(clusterMgtController)
{

}

ClusterMgtConnectionAcceptor::~ClusterMgtConnectionAcceptor()
{

}

void ClusterMgtConnectionAcceptor::onAccept(int fd,
                                         const Network::IpSocketEndpoint& localEndPoint,
                                         const Network::IpSocketEndpoint& remoteEndPoint)
{
    createClusterConnection(fd, localEndPoint, remoteEndPoint);
}

void ClusterMgtConnectionAcceptor::createClusterConnection(int fd,
                                                        const Network::IpSocketEndpoint& localEndpoint,
                                                        const Network::IpSocketEndpoint& remoteEndpoint)
{
    std::shared_ptr<Ipc::IIpcConnectionReceiver>
            clustersMgtConnectionReceiver(new ClusterMgtConnectionReceiver(clientType_,
                                                                           clusterMgtController_,
                                                                           remoteEndpoint));


    IpcMessageFactories factories;
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new SystemMonitorMessage::SystemMonitorMessageFactory()));
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new IpcMessage::IpcLayerMessageFactory()));

    Ipc::IIpcClient* tcpAcceptedClientPtr =
            Ipc::IpcClientCreator::CreateWithTcpClientStrategy(fd, localEndpoint, remoteEndpoint, clustersMgtConnectionReceiver, factories);
    std::shared_ptr<Ipc::IIpcClient> ipcClient(tcpAcceptedClientPtr);

    clusterMgtController_->addAcceptedIpcClient(remoteEndpoint, ipcClient, clientType_);
}

}
