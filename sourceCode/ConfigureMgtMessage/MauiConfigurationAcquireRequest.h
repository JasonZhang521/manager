#ifndef _CONFIGUREMGTMESSAGE_MANUICONFIGURATIONACQUIREREQUEST_H_
#define _CONFIGUREMGTMESSAGE_MANUICONFIGURATIONACQUIREREQUEST_H_
#include "IConfigureMgtMessage.h"

namespace ConfigureMgtMessage {

class MauiConfigurationAcquireRequest : public IConfigureMgtMessage
{
public:
    MauiConfigurationAcquireRequest();
    ~MauiConfigurationAcquireRequest();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::IpcConfigureMgtMessageType getConfigureMgtType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};
}
#endif // _CONFIGUREMGTMESSAGE_MANUICONFIGURATIONACQUIREREQUEST_H_
