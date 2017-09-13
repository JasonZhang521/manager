#ifndef _CLUSTERMANAGEMENT_ICLUSTERMGTCLIENTSMANAGEMENT_H_
#define _CLUSTERMANAGEMENT_ICLUSTERMGTCLIENTSMANAGEMENT_H_
#include "ClusterMgtClientType.h"
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

class IClusterMgtClientsManagement
{
public:
    IClusterMgtClientsManagement();
    virtual ~IClusterMgtClientsManagement();
    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void addAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, std::shared_ptr<Ipc::IIpcClient> ipcClient) = 0;
    virtual void removeAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint) = 0;
    virtual void handleMessage(IpcMessage::IIpcMessage& msg, ClientType fromClientType, const Network::IpSocketEndpoint& remoteIpEndpoint) = 0;
};
}

#endif // _CLUSTERMANAGEMENT_ICLUSTERMGTCLIENTSMANAGEMENT_H_
