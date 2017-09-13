#include "SystemMonitorMessageFactory.h"
#include "ComputerNodeInfoReport.h"
#include "ComputerNodeInfoRequest.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "Trace.h"

namespace SystemMonitorMessage {

SystemMonitorMessageFactory::SystemMonitorMessageFactory()
    :IpcMessage::IIpcMessageFactory(IpcMessage::IpcMessage_SystemMonitor)
{

}

SystemMonitorMessageFactory::~SystemMonitorMessageFactory()
{

}

IpcMessage::IIpcMessage* SystemMonitorMessageFactory::createMessage(IpcMessage::IpcMessageApplicationIntType type) const
{
    if (static_cast<IpcMessage::SystemMonitorMessageType>(type) == IpcMessage::ComputerNodeInfoRequestMessage)
    {
        return new ComputerNodeInfoRequest();
    }
    else if (static_cast<IpcMessage::SystemMonitorMessageType>(type) == IpcMessage::ComputerNodeInfoReportMessage)
    {
        return new ComputerNodeInfoReport();
    }
    if (static_cast<IpcMessage::SystemMonitorMessageType>(type) == IpcMessage::ControlNodeBrieflyInfoRequestMessage)
    {
        return new ControlNodeBrieflyInfoRequest();
    }
    else if (static_cast<IpcMessage::SystemMonitorMessageType>(type) == IpcMessage::ControlNodeBrieflyInfoResponseMessage)
    {
        return new ControlNodeBrieflyInfoResponse();
    }
    else
    {
        TRACE_ERROR("Only support message type: MonitorRequest and MonitorMessage!");
        return nullptr;
    }
}
}
