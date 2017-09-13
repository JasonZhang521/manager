#ifndef _IPCMESSAGE_IPCHEARTBEATREPORT_H_
#define _IPCMESSAGE_IPCHEARTBEATREPORT_H_
#include "IIpcComunicationMessage.h"
namespace IpcMessage {
class IpcHeartbeatReport : public IIpcComunicationMessage
{
public:
    IpcHeartbeatReport();
    virtual ~IpcHeartbeatReport();
    virtual IpcCommunicationMessageType getComunicationMessageType() const;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);
    virtual std::ostream& operator<< (std::ostream& os) const;
};
}

#endif // _IPCMESSAGE_IPCHEARTBEATREPORT_H_
