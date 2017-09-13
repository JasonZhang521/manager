#ifndef CLUSTERMGTMESSAGEFACTORY_H
#define CLUSTERMGTMESSAGEFACTORY_H
#include "IIpcMessageFactory.h"
#include "Component.h"
#include "Macro.h"

namespace ClusterMgtMessage {
class ClusterMgtMessageFactory : public IpcMessage::IIpcMessageFactory
{
public:
    ClusterMgtMessageFactory();
    virtual ~ClusterMgtMessageFactory();
    virtual IpcMessage::IIpcMessage* createMessage(IpcMessage::IpcMessageApplicationIntType type) const;
public:
    GETCLASSNAME(ClusterMgtMessageFactory)
};

}

#endif // CLUSTERMGTMESSAGEFACTORY_H
