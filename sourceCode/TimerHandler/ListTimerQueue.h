#ifndef _TIMER_LISTTIMERQUEUE_H_
#define _TIMER_LISTTIMERQUEUE_H_
#include "ITimerQueue.h"
#include "Component.h"
#include "Macro.h"
#include <list>

namespace TimerHandler {
class ITimer;

class ListTimerQueue : public ITimerQueue
{
    struct TimerCache
    {
        enum Op{
            Add,
            Delete
        };
        Op op_;
        uint64_t timerId_;
        ITimer* timer_;
        TimerCache(Op op, uint64_t timerId, ITimer* timer)
            :op_(op), timerId_(timerId), timer_(timer)
        {}
    };
    bool isExecuting_;
    using TimersList = std::list<ITimer*>;
    TimersList timersList_;
    using TimersCacheList = std::list<TimerCache>;
    TimersCacheList timersCacheList_;
public:
    ListTimerQueue();
    virtual ~ListTimerQueue();
protected:
    virtual void addTimer(ITimer*);
    virtual void deleteTimer(uint64_t timerID);
    virtual void executeTimers();
    virtual std::ostream& operator<<(std::ostream& os) const;

private:
    void refreshTimers();

public:
     GETCLASSNAME(ListTimerQueue)
};

}

#endif // _TIMER_LISTTIMERQUEUE_H_
