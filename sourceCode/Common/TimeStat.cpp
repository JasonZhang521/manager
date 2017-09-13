#include "TimeStat.h"
#include "SystemTime.h"

TimeStat::TimeStat()
: startTime_(SystemTime::currentTimeStampAsMillisecond())
{

}

void TimeStat::restart()
{
    startTime_ = SystemTime::currentTimeStampAsMillisecond();
}

uint64_t TimeStat::getElapseTimeAsMilliSecond()
{
    uint64_t currentTime = SystemTime::currentTimeStampAsMillisecond();
    return (currentTime - startTime_);
}

uint64_t TimeStat::getElapseTimeAsSecond()
{
    return getElapseTimeAsMilliSecond() / 1000;
}
