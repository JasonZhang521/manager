#include "ControlNodeBrieflyInfoResponse.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
namespace SystemMonitorMessage {
ControlNodeBrieflyInfoResponse::ControlNodeBrieflyInfoResponse()
{

}

ControlNodeBrieflyInfoResponse::~ControlNodeBrieflyInfoResponse()
{

}

void ControlNodeBrieflyInfoResponse::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_SystemMonitor));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ControlNodeBrieflyInfoResponseMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
    systemInfoBriefly_.serialize(writeBuffer);
}
void ControlNodeBrieflyInfoResponse::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
    systemInfoBriefly_.unserialize(readBuffer);
}

IpcMessage::SystemMonitorMessageType ControlNodeBrieflyInfoResponse::getSystemMonitorType() const
{
    return IpcMessage::ControlNodeBrieflyInfoResponseMessage;
}

std::ostream& ControlNodeBrieflyInfoResponse::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_SystemMonitor)
       << ", clusterMgtType=" << IpcMessage::SystemMonitorTypeString(IpcMessage::ControlNodeBrieflyInfoResponseMessage)
       << ", systemInfoBriefly=" << systemInfoBriefly_
       << "]";
    return os;
}

void ControlNodeBrieflyInfoResponse::setSystemInfoBriefly(const Environment::SystemInfoBriefly& info)
{
    systemInfoBriefly_ = info;
}

const Environment::SystemInfoBriefly& ControlNodeBrieflyInfoResponse::getSystemInfoBriefly() const
{
    return systemInfoBriefly_;
}


}
