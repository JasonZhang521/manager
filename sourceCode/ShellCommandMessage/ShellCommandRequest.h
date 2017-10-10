#ifndef _SHELLCOMMANDMESSAGE_SHELLCOMMANDREQUEST_H_
#define _SHELLCOMMANDMESSAGE_SHELLCOMMANDREQUEST_H_
#include "IShellCommandMessage.h"
#include "ShellCommandDataType.h"

namespace ShellCommandMessage {

class ShellCommandRequest : public IShellCommandMessage
{
    Environment::ShellCommandType commandType_;
public:
    ShellCommandRequest();
    ~ShellCommandRequest();
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);

    virtual IpcMessage::IpcShellCommandMessageType getShellCommandMessageType() const;
    virtual std::ostream& operator<< (std::ostream& os) const;

    void setShellCommandType(Environment::ShellCommandType commandType);
    Environment::ShellCommandType getShellCommandType() const;
};

}

#endif // _SHELLCOMMANDMESSAGE_SHELLCOMMANDREQUEST_H_
