#include "IpcConnectionTimer.h"
#include "IpcConnectionTcpClientStrategy.h"
#include "IIpcConnectionReceiver.h"
#include "ITimer.h"
#include "AppConst.h"
#include "Trace.h"

namespace Ipc {

IpcConnectionTimer::IpcConnectionTimer(IIpcConnectionClientStrategy* clientStrategy,
                                       IIpcConnectionReceiver* connectionReceiver)
    : TimerHandler::ITimer(ConnectionTimeout, TimerHandler::TimerType::SingleTimer)
    , clientStrategy_(clientStrategy)
    , connectionReceiver_(connectionReceiver)
{

}

IpcConnectionTimer::~IpcConnectionTimer()
{  
}

void IpcConnectionTimer::onTime()
{
    TRACE_WARNING("Don't receive any message of heartbeat, disconnect!");
    if (clientStrategy_)
    {
        clientStrategy_->disconnect();
    }
}

std::ostream& IpcConnectionTimer::operator<<(std::ostream& os)
{
    TimerHandler::ITimer::print(os);
    return os;
}

}
