#ifndef IPCAUTHORIZATIONRESPONSE_H
#define IPCAUTHORIZATIONRESPONSE_H
#include "IIpcComunicationMessage.h"

namespace IpcMessage {
class IpcAuthorizationResponse : public IIpcComunicationMessage
{
public:
    IpcAuthorizationResponse();    
    virtual ~IpcAuthorizationResponse();
private:
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);
    virtual IpcCommunicationMessageType getComunicationMessageType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};
}
#endif // IPCAUTHORIZATIONRESPONSE_H
