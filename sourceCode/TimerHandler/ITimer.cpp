#include "ITimer.h"
#include "SystemTime.h"
#include "TimerIdGenerator.h"
#include "LoopMain.h"

namespace TimerHandler {

std::string timerTypeToString(TimerType type)
{
    switch (type) {
    case TimerType::PeriodTimer:
        return std::string("PeriodTimer");
    case TimerType::SingleTimer:
        return std::string("SingleTimer");
    default:
        return std::string("NoTimer");;
    }
}

ITimer::ITimer(uint64_t period, TimerType type)
    :timerId_(TimerIdGenerator::generateTimerId())
    ,period_(period)
    ,expiredTime_(SystemTime::expiredTimeStampAsMillisecond(period))
    ,timerType_(type)
{

}

ITimer::~ITimer()
{
    Core::LoopMain::instance().deRegisterTimer(timerId_);
}

uint64_t ITimer::getTimerId() const
{
    return timerId_;
}

bool ITimer::isExpired()
{
    return (SystemTime::currentTimeStampAsMillisecond() > expiredTime_);
}

uint64_t ITimer::getExpiredTime() const
{
    return expiredTime_;
}

uint64_t ITimer::getPeriod() const
{
    return period_;
}

TimerType ITimer::getTimerType() const
{
    return timerType_;
}


void ITimer::resetTimer(uint64_t period)
{
    if (period == 0)
    {
        expiredTime_ = SystemTime::expiredTimeStampAsMillisecond(period_);
    }
    else
    {
       expiredTime_ = SystemTime::expiredTimeStampAsMillisecond(period);
    }
}

void ITimer::print(std::ostream& os)
{
    os << "["
       << "timerId=" << getTimerId()
       << ", period=" << getPeriod()
       << ", expiredTime=" << getExpiredTime()
       << ", timerType=" << timerTypeToString(getTimerType())
       << "]";
}


std::ostream& operator<<(std::ostream& os, ITimer* timer)
{
    return timer->operator<<(os);
}

}
