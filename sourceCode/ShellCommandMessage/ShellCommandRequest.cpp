#include "ShellCommandRequest.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "Generic.h"
namespace ShellCommandMessage {

ShellCommandRequest::ShellCommandRequest()
{
}

ShellCommandRequest::~ShellCommandRequest()
{

}

void ShellCommandRequest::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessage_ShellCommand));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ShellCommandRequestMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
    writeBuffer.write(static_cast<uint8_t>(toIntegral(commandType_)));
}

void ShellCommandRequest::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
    uint8_t commandType;
    readBuffer.read(commandType);
    commandType_ = Environment::ShellCommandType(commandType);
}

IpcMessage::IpcShellCommandMessageType ShellCommandRequest::getShellCommandMessageType() const
{
    return IpcMessage::ShellCommandRequestMessage;
}

std::ostream& ShellCommandRequest::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ShellCommand)
       << ", shellCommandMessageType=" << IpcMessage::IpcShellCommandTypeToString(IpcMessage::ShellCommandRequestMessage)
       << ", commandType=" << Environment::ShellCommand::getCmdString(commandType_)
       << "]";
    return os;
}

void ShellCommandRequest::setShellCommandType(Environment::ShellCommandType commandType)
{
    commandType_ = commandType;
}

Environment::ShellCommandType ShellCommandRequest::getShellCommandType() const
{
    return commandType_;
}

}
