#include "IpcAuthorizationRequest.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace IpcMessage {

IpcAuthorizationRequest::IpcAuthorizationRequest()
{

}

IpcAuthorizationRequest::~IpcAuthorizationRequest()
{

}

void IpcAuthorizationRequest::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage_IpcCommunication));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcAuthorizationRequstMessage));
    IIpcMessage::write(writeBuffer);
}

void IpcAuthorizationRequest::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IIpcMessage::read(readBuffer);
}

IpcCommunicationMessageType IpcAuthorizationRequest::getComunicationMessageType() const
{
    return IpcAuthorizationRequstMessage;
}

std::ostream& IpcAuthorizationRequest::operator<< (std::ostream& os) const
{
    os << "["
       << ", ipcMessageType=" << IpcMessageTypeString(IpcMessage_IpcCommunication)
       << ", IpcHeartbeatType=" << IpcCommunicationTypeString(IpcAuthorizationRequstMessage);
    IpcMessage::IIpcMessage::print(os);
    return os;
}

}
