#ifndef _TIMERHANDLER_ITIMERQUEUE_H_
#define _TIMERHANDLER_ITIMERQUEUE_H_
#include <stdint.h>
#include <ostream>

namespace TimerHandler {

class ITimer;

class ITimerQueue
{
public:
    ITimerQueue();
    virtual ~ITimerQueue();
    virtual void addTimer(ITimer*) = 0;
    virtual void deleteTimer(uint64_t timerID) = 0;
    virtual void executeTimers() = 0;
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, ITimerQueue* timerQueue);

}
#endif // _TIMERHANDLER_ITIMERQUEUE_H_
