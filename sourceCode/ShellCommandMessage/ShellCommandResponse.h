#ifndef _SHELLCOMMANDMESSAGE_SHELLCOMMANDRESPONSE_H_
#define _SHELLCOMMANDMESSAGE_SHELLCOMMANDRESPONSE_H_
#include "IShellCommandMessage.h"

namespace ShellCommandMessage {
class ShellCommandResponse : public IShellCommandMessage
{
public:
    ShellCommandResponse();
    ~ShellCommandResponse();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::IpcShellCommandMessageType getShellCommandMessageType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;
};

}

#endif // _SHELLCOMMANDMESSAGE_SHELLCOMMANDRESPONSE_H_
