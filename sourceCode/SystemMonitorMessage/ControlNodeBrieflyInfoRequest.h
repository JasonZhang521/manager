#ifndef _SYSTEMMONITORMESSAGE_CONTROLNODEBRIEFLYINFOREQUEST_H_
#define _SYSTEMMONITORMESSAGE_CONTROLNODEBRIEFLYINFOREQUEST_H_
#include "ISystemMonitorMessage.h"

namespace SystemMonitorMessage {
class ControlNodeBrieflyInfoRequest : public ISystemMonitorMessage
{
public:
    ControlNodeBrieflyInfoRequest();
    ~ControlNodeBrieflyInfoRequest();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::SystemMonitorMessageType getSystemMonitorType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};
}

#endif // _SYSTEMMONITORMESSAGE_CONTROLNODEBRIEFLYINFOREQUEST_H_
