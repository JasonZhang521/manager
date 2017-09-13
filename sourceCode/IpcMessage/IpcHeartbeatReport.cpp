#include "IpcHeartbeatReport.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
namespace IpcMessage {

IpcHeartbeatReport::IpcHeartbeatReport()
{

}

IpcHeartbeatReport::~IpcHeartbeatReport()
{

}

IpcCommunicationMessageType IpcHeartbeatReport::getComunicationMessageType() const
{
    return IpcMessage::IpcCommunicationMessageType::IpcHeartbeatReportMessage;
}

void IpcHeartbeatReport::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage_IpcCommunication));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcHeartbeatReportMessage));
    IIpcMessage::write(writeBuffer);
}
void IpcHeartbeatReport::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IIpcMessage::read(readBuffer);
}

std::ostream& IpcHeartbeatReport::operator<< (std::ostream& os) const
{
    os << "["
       << ", ipcMessageType=" << IpcMessageTypeString(IpcMessage_IpcCommunication)
       << ", IpcHeartbeatType=" << IpcCommunicationTypeString(IpcHeartbeatReportMessage);
    IpcMessage::IIpcMessage::print(os);
    return os;
}

}
