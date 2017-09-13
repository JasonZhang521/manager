#ifndef _CONFIGUREMGTMESSAGE_ICONFIGUREMGTMESSAGE_H_
#define _CONFIGUREMGTMESSAGE_ICONFIGUREMGTMESSAGE_H_
#include "IIpcMessage.h"
#include "IpcMessageType.h"

namespace ConfigureMgtMessage {

class IConfigureMgtMessage : public IpcMessage::IIpcMessage
{
public:
    IConfigureMgtMessage();
    virtual ~IConfigureMgtMessage();
    virtual IpcMessage::IpcMessageType getMessageType() const;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const = 0;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer) = 0;

    virtual IpcMessage::IpcConfigureMgtMessageType getConfigureMgtType() const = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
};

}
#endif // _CONFIGUREMGTMESSAGE_ICONFIGUREMGTMESSAGE_H_
