#ifndef _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATEREQUEST_H_
#define _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATEREQUEST_H_
#include "IConfigureMgtMessage.h"
#include "MauiConfig.h"

namespace ConfigureMgtMessage {

enum ConfigureUpdateType
{
    REPLACE_FILE,
    REPLACE_RECORD
};

class MauiConfigurationUpdateRequest : public IConfigureMgtMessage
{
    ConfigureUpdateType updateType_;
    ConfigureManagement::MauiConfig mauiConfig_;
public:
    MauiConfigurationUpdateRequest();
    ~MauiConfigurationUpdateRequest();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::IpcConfigureMgtMessageType getConfigureMgtType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;

    void setMauiConfig(const ConfigureManagement::MauiConfig& config);
    const ConfigureManagement::MauiConfig&  getMauiConfig() const;
};

}

#endif // _CONFIGUREMGTMESSAGE_MAUICONFIGURATIONUPDATEREQUEST_H_
