#include "ComputerNodeInfoReport.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "Trace.h"
#include "App.h"
#include <stdint.h>

namespace SystemMonitorMessage {

ComputerNodeInfoReport::ComputerNodeInfoReport()
{

}

ComputerNodeInfoReport::ComputerNodeInfoReport(const Environment::CpuUsageInfo& cpuUsageInfo,
                                     const Environment::SystemInfoBriefly& systemInfoBriefly)
    : cpuUsageInfo_(cpuUsageInfo)
    , systemInfoBriefly_(systemInfoBriefly)
{
}

ComputerNodeInfoReport::~ComputerNodeInfoReport()
{

}

void ComputerNodeInfoReport::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    TRACE_ENTER();
    write(writeBuffer);
}

void ComputerNodeInfoReport::unserialize(Serialize::ReadBuffer& readBuffer)
{
    TRACE_ENTER();
    read(readBuffer);
}

IpcMessage::SystemMonitorMessageType ComputerNodeInfoReport::getSystemMonitorType() const
{
    return IpcMessage::ComputerNodeInfoReportMessage;
}

std::ostream& ComputerNodeInfoReport::operator<< (std::ostream& os) const
{
    print(os);
    return os;
}

void ComputerNodeInfoReport::write(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_SystemMonitor));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ComputerNodeInfoReportMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
    cpuUsageInfo_.serialize(writeBuffer);
    systemInfoBriefly_.serialize(writeBuffer);
}

void ComputerNodeInfoReport::read(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read<uint8_t>(temp);
    IpcMessage::IpcMessageType type = static_cast<IpcMessage::IpcMessageType>(temp);
    if (type != IpcMessage::IpcMessageType::IpcMessage_SystemMonitor)
    {
        TRACE_ERROR("Receive IPC message with error message type:" << type);
        throw std::runtime_error("Receive IPC message with error message type");
    }
    readBuffer.read<uint8_t>(temp);
    IpcMessage::SystemMonitorMessageType systemMonitorType = static_cast<IpcMessage::SystemMonitorMessageType>(temp);
    if (systemMonitorType != IpcMessage::ComputerNodeInfoReportMessage)
    {
        TRACE_ERROR("Receive system infomation message with error system monitor type:" << IpcMessage::ComputerNodeInfoReportMessage);
        throw std::invalid_argument("Receive system infomation message with error system monitor type:");
    }
    IpcMessage::IIpcMessage::read(readBuffer);
    cpuUsageInfo_.unserialize(readBuffer);
    systemInfoBriefly_.unserialize(readBuffer);
}

void ComputerNodeInfoReport::print(std::ostream& os) const
{
    os << "["
       << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_SystemMonitor)
       << ", systemMonitorType=" << IpcMessage::SystemMonitorTypeString(IpcMessage::ComputerNodeInfoReportMessage);
    IpcMessage::IIpcMessage::print(os);
    os << ", cpuUsageInfo=" << cpuUsageInfo_
       << ", systemInfoBriefly=" << systemInfoBriefly_
       << "]";
}

}
