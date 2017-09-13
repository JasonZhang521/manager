#ifndef CLUSTERMGTCONTROLLER_H
#define CLUSTERMGTCONTROLLER_H
#include "IClusterMgtController.h"
#include "ClusterMgtClientType.h"
#include "Component.h"
#include "Macro.h"
#include <map>
#include <memory>

namespace Network
{
class IpSocketEndpoint;
}

namespace ClusterManagement {

class IClusterMgtClientsManagement;

class ClusterMgtController : public IClusterMgtController
{
    using ClientsManagementMap = std::map<ClientType, std::unique_ptr<IClusterMgtClientsManagement> >;
    ClientsManagementMap clientsManager_;
public:
    ClusterMgtController();
    virtual ~ClusterMgtController();
    virtual void startup();
    virtual void shutdown();
    virtual void addAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, std::shared_ptr<Ipc::IIpcClient> ipcClient, ClientType type);
    virtual void removeAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, ClientType type);
    virtual void handleMessage(IpcMessage::IIpcMessage& msg, ClientType fromClientType, const Network::IpSocketEndpoint& remoteIpEndpoint);
    virtual void addClientManager(ClientType type, std::unique_ptr<IClusterMgtClientsManagement> clientManager);

public:
    GETCLASSNAME(ClusterMgtController)
};

}

#endif // CLUSTERMGTCONTROLLER_H
