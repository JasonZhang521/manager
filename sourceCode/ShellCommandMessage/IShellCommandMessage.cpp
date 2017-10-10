#include "IShellCommandMessage.h"

namespace ShellCommandMessage {

IShellCommandMessage::IShellCommandMessage()
{

}

IShellCommandMessage::~IShellCommandMessage()
{

}

IpcMessage::IpcMessageType IShellCommandMessage::getMessageType() const
{
    return IpcMessage::IpcMessageType::IpcMessage_ShellCommand;
}

}
