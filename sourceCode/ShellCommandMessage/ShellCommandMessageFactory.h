#ifndef _SHELLCOMMANDMESSAGE_SHELLCOMMANDMESSAGEFACTORY_H_
#define _SHELLCOMMANDMESSAGE_SHELLCOMMANDMESSAGEFACTORY_H_
#include "IIpcMessageFactory.h"
#include "Component.h"
#include "Macro.h"

namespace ShellCommandMessage {
class ShellCommandMessageFactory
{
public:
    ShellCommandMessageFactory();
    ~ShellCommandMessageFactory();
    virtual IpcMessage::IIpcMessage* createMessage(IpcMessage::IpcMessageApplicationIntType type) const;
public:
    GETCLASSNAME(ShellCommandMessageFactory)
};
}

#endif // _SHELLCOMMANDMESSAGE_SHELLCOMMANDMESSAGEFACTORY_H_
