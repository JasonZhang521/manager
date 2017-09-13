#ifndef IPCAUTHORIZATIONREQUEST_H
#define IPCAUTHORIZATIONREQUEST_H
#include "IIpcComunicationMessage.h"

namespace IpcMessage {

class IpcAuthorizationRequest : public IIpcComunicationMessage
{
public:
    IpcAuthorizationRequest();
    virtual ~IpcAuthorizationRequest();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcCommunicationMessageType getComunicationMessageType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};

}

#endif // IPCAUTHORIZATIONREQUEST_H
