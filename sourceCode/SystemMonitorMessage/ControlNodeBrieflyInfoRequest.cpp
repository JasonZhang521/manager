#include "ControlNodeBrieflyInfoRequest.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace SystemMonitorMessage {
ControlNodeBrieflyInfoRequest::ControlNodeBrieflyInfoRequest()
{

}

ControlNodeBrieflyInfoRequest::~ControlNodeBrieflyInfoRequest()
{

}

void ControlNodeBrieflyInfoRequest::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_SystemMonitor));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ControlNodeBrieflyInfoRequestMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
}

void ControlNodeBrieflyInfoRequest::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
}

IpcMessage::SystemMonitorMessageType ControlNodeBrieflyInfoRequest::getSystemMonitorType() const
{
    return IpcMessage::ControlNodeBrieflyInfoRequestMessage;
}

std::ostream& ControlNodeBrieflyInfoRequest::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_SystemMonitor)
       << ", clusterMgtType=" << IpcMessage::SystemMonitorTypeString(IpcMessage::ControlNodeBrieflyInfoRequestMessage)
       << "]";
    return os;
}
}
