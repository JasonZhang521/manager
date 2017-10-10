#ifndef _SHELLCOMMANDMESSAGE_ISHELLCOMMANDMESSAGE_H_
#define _SHELLCOMMANDMESSAGE_ISHELLCOMMANDMESSAGE_H_
#include "IIpcMessage.h"

namespace ShellCommandMessage {

class IShellCommandMessage : public IpcMessage::IIpcMessage
{
public:
    IShellCommandMessage();
    virtual ~IShellCommandMessage();
    virtual IpcMessage::IpcMessageType getMessageType() const;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const = 0;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer) = 0;

    virtual IpcMessage::IpcShellCommandMessageType getShellCommandMessageType() const = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
};

}

#endif // _SHELLCOMMANDMESSAGE_ISHELLCOMMANDMESSAGE_H_
