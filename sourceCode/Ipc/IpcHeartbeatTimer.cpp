#include "IpcHeartbeatTimer.h"
#include "IIpcConnectionClientStrategy.h"
#include "IpcLayerMessageFactory.h"
#include "IpcHeartbeatReport.h"
#include "AppConst.h"
#include "Trace.h"
#include <memory>

namespace Ipc {
IpcHeartbeatTimer::IpcHeartbeatTimer(IIpcConnectionClientStrategy* clientStrategy)
    : TimerHandler::ITimer(HeartbeatPeriod, TimerHandler::TimerType::PeriodTimer)
    , clientStrategy_(clientStrategy)
{

}

IpcHeartbeatTimer::~IpcHeartbeatTimer()
{

}

void IpcHeartbeatTimer::IpcHeartbeatTimer::onTime()
{
    TRACE_DEBUG("Send heartbeat!");
    IpcMessage::IpcLayerMessageFactory factory;
    std::shared_ptr<IpcMessage::IIpcMessage>
            message(factory.createMessage(IpcMessage::IpcHeartbeatReportMessage));
    if (clientStrategy_ && message)
    {
        clientStrategy_->send(*message);
    }
}
std::ostream& IpcHeartbeatTimer::operator<<(std::ostream& os)
{
    TimerHandler::ITimer::print(os);
    return os;
}
}
