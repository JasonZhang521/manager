#ifndef _TIMERHANDLER_ITIMER_H_
#define _TIMERHANDLER_ITIMER_H_
#include <stdint.h>
#include <ostream>

namespace TimerHandler {

enum class TimerType
{
    PeriodTimer,
    SingleTimer
};

std::string timerTypeToString(TimerType type);

class ITimer
{
protected:
    const uint64_t timerId_;
    const uint64_t period_;
    uint64_t expiredTime_;
    TimerType timerType_;
public:
    ITimer(uint64_t period, TimerType type = TimerType::SingleTimer);
    virtual ~ITimer();
    virtual void onTime() = 0;
    virtual std::ostream& operator<<(std::ostream& os) = 0;
    bool isExpired();
    uint64_t getTimerId() const;
    uint64_t getExpiredTime() const;
    uint64_t getPeriod() const;
    TimerType getTimerType() const;
    void resetTimer(uint64_t period = 0);
protected:
    void print(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, ITimer* timer);

}

#endif // _TIMERHANDLER_ITIMER_H_
