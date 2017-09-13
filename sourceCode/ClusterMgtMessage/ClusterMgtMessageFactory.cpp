#include "ClusterMgtMessageFactory.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "Trace.h"
namespace ClusterMgtMessage {
ClusterMgtMessageFactory::ClusterMgtMessageFactory()
    :IpcMessage::IIpcMessageFactory(IpcMessage::IpcMessage_ClusterMgt)
{

}

ClusterMgtMessageFactory::~ClusterMgtMessageFactory()
{

}

IpcMessage::IIpcMessage* ClusterMgtMessageFactory::createMessage(IpcMessage::IpcMessageApplicationIntType type) const
{
    if (static_cast<IpcMessage::IpcClusterMgtMessageType>(type) == IpcMessage::ControlNodeBrieflyInfoRequestMessage)
    {
        return new ControlNodeBrieflyInfoRequest();
    }
    else if (static_cast<IpcMessage::IpcClusterMgtMessageType>(type) == IpcMessage::ControlNodeBrieflyInfoResponseMessage)
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
