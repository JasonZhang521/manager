#ifndef ICLUSTERMGTMESSAGE_H
#define ICLUSTERMGTMESSAGE_H
#include "IIpcMessage.h"
#include "IpcMessageType.h"

namespace ClusterMgtMessage {

class IClusterMgtMessage : public IpcMessage::IIpcMessage
{
public:
    IClusterMgtMessage();
    virtual ~IClusterMgtMessage();
    virtual IpcMessage::IpcMessageType getMessageType() const;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const = 0;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer) = 0;

    virtual IpcMessage::IpcClusterMgtMessageType getClusterMgtType() const = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
};

}
#endif // ICLUSTERMGTMESSAGE_H
