#include "IpcAuthorizationResponse.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace IpcMessage {
IpcAuthorizationResponse::IpcAuthorizationResponse()
{

}
IpcAuthorizationResponse::~IpcAuthorizationResponse()
{

}

void IpcAuthorizationResponse::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage_IpcCommunication));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcAuthorizationResponseMessage));
    IIpcMessage::write(writeBuffer);
}

void IpcAuthorizationResponse::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IIpcMessage::read(readBuffer);
}

IpcCommunicationMessageType IpcAuthorizationResponse::getComunicationMessageType() const
{
    return IpcAuthorizationResponseMessage;
}

std::ostream& IpcAuthorizationResponse::operator<< (std::ostream& os) const
{
    os << "["
       << ", ipcMessageType=" << IpcMessageTypeString(IpcMessage_IpcCommunication)
       << ", IpcHeartbeatType=" << IpcCommunicationTypeString(IpcAuthorizationRequstMessage);
    IpcMessage::IIpcMessage::print(os);
    return os;
}

}
