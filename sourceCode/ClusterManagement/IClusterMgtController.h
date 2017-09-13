#ifndef ICLUSTERMGTCONTROLLER_H
#define ICLUSTERMGTCONTROLLER_H
#include "ClusterMgtClientType.h"
#include <string>
#include <memory>

namespace Network {
class IpSocketEndpoint;
}

namespace Ipc {
class IIpcClient;
}

namespace IpcMessage {
class IIpcMessage;
}

namespace ClusterManagement {
class IClusterMgtClientsManagement;

class IClusterMgtController
{
public:
    IClusterMgtController();
    ~IClusterMgtController();
    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void addAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, std::shared_ptr<Ipc::IIpcClient> ipcClient, ClientType type) = 0;
    virtual void removeAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, ClientType type) = 0;
    virtual void handleMessage(IpcMessage::IIpcMessage& msg, ClientType fromClientType, const Network::IpSocketEndpoint& remoteIpEndpoint) = 0;
    virtual void addClientManager(ClientType type, std::unique_ptr<IClusterMgtClientsManagement> clientManager) = 0;
};
}
#endif // ICLUSTERMGTCONTROLLER_H
