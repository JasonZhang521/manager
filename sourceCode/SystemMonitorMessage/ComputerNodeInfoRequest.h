#ifndef _SYSTEMMONITORMESSAGE_COMPUTERNODEINFOREQUEST_H_
#define _SYSTEMMONITORMESSAGE_COMPUTERNODEINFOREQUEST_H_
#include "ISystemMonitorMessage.h"
#include "Component.h"
#include "Macro.h"

namespace SystemMonitorMessage {

class ComputerNodeInfoRequest : public ISystemMonitorMessage
{
public:
    ComputerNodeInfoRequest();
protected:
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);
    virtual IpcMessage::SystemMonitorMessageType getSystemMonitorType() const;
    std::ostream& operator<< (std::ostream& os) const;

public:
    GETCLASSNAME(SystemInfoRequest)
};

}

#endif // _SYSTEMMONITORMESSAGE_COMPUTERNODEINFOREQUEST_H_
