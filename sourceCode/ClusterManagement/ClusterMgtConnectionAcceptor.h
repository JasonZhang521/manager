#ifndef _CLUSTERMANAGEMENT_CLUSTERMGTCONNECTIONACCEPTOR_H_
#define _CLUSTERMANAGEMENT_CLUSTERMGTCONNECTIONACCEPTOR_H_
#include "IIpcConnectionAcceptor.h"
#include "ClusterMgtClientType.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace ClusterManagement {

class IClusterMgtController;

class ClusterMgtConnectionAcceptor : public Ipc::IIpcConnectionAcceptor
{
    ClientType clientType_;
    std::shared_ptr<IClusterMgtController> clusterMgtController_;
public:
    ClusterMgtConnectionAcceptor(ClientType type, std::shared_ptr<IClusterMgtController> clusterMgtController);
    ~ClusterMgtConnectionAcceptor();
    virtual void onAccept(int fd,
                          const Network::IpSocketEndpoint& localEndPoint,
                          const Network::IpSocketEndpoint& remoteEndPoint);
private:
    void createClusterConnection(int fd,
                                 const Network::IpSocketEndpoint& localEndPoint,
                                 const Network::IpSocketEndpoint& remoteEndPoint);
public:
    GETCLASSNAME(ClusterMgtConnectionAcceptor)
};

}
#endif // _CLUSTERMANAGEMENT_CLUSTERMGTCONNECTIONACCEPTOR_H_
