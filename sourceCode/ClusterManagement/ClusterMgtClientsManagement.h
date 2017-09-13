#ifndef _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTSMANAGEMENT_H_
#define _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTSMANAGEMENT_H_
#include "IClusterMgtClientsManagement.h"
#include "IpSocketEndpoint.h"
#include "Component.h"
#include "Macro.h"
#include <map>
#include <memory>

namespace Ipc {
class IIpcServer;
}

namespace Network {
class IpSocketEndpoint;
}

namespace ClusterManagement {

class ClusterMgtClientsManagment : public IClusterMgtClientsManagement
{
    ClientType clientType_;
    using IpcClientsMap = std::map<Network::IpSocketEndpoint, std::shared_ptr<Ipc::IIpcClient> >;
    IpcClientsMap clients_;
    std::shared_ptr<Ipc::IIpcServer> ipcServer_;
public:
    ClusterMgtClientsManagment(ClientType clientType, std::shared_ptr<Ipc::IIpcServer> ipcServer);
    virtual ~ClusterMgtClientsManagment();
    virtual void startup();
    virtual void shutdown();
    virtual void addAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, std::shared_ptr<Ipc::IIpcClient> ipcClient);
    virtual void removeAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint);
    virtual void handleMessage(IpcMessage::IIpcMessage& msg, ClientType fromClientType, const Network::IpSocketEndpoint& remoteIpEndpoint);
private:
    void forwardIpcMessage(const Network::IpSocketEndpoint& remoteEndPoint, IpcMessage::IIpcMessage& msg);
    void broadcastMsg(IpcMessage::IIpcMessage& msg);
    void handleClusterMgtMessage(const IpcMessage::IIpcMessage& msg, const Network::IpSocketEndpoint& remoteIpEndpoint);

public:
    GETCLASSNAME(ClusterMgtClientsManagment)
};

}

#endif // _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTSMANAGEMENT_H_
