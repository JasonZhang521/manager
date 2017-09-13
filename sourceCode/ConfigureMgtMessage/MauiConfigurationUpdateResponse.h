#ifndef _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATERESPONSE_H_
#define _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATERESPONSE_H_
#include "IConfigureMgtMessage.h"

namespace ConfigureMgtMessage {

class MauiConfigurationUpdateResponse : IConfigureMgtMessage
{
public:
    MauiConfigurationUpdateResponse();
    ~MauiConfigurationUpdateResponse();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::IpcConfigureMgtMessageType getConfigureMgtType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};
}

#endif // _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATERESPONSE_H_
