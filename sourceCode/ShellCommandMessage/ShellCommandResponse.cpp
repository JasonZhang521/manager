#include "ShellCommandResponse.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace ShellCommandMessage {
ShellCommandResponse::ShellCommandResponse()
{

}


ShellCommandResponse::~ShellCommandResponse()
{

}

void ShellCommandResponse::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessage_ShellCommand));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ShellCommandResponseMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
}

void ShellCommandResponse::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
}

IpcMessage::IpcShellCommandMessageType ShellCommandResponse::getShellCommandMessageType() const
{
    return IpcMessage::ShellCommandResponseMessage;
}

std::ostream& ShellCommandResponse::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ShellCommand)
       << ", shellCommandMessageType=" << IpcMessage::IpcShellCommandTypeToString(IpcMessage::ShellCommandResponseMessage)
       << "]";
    return os;
}

}
