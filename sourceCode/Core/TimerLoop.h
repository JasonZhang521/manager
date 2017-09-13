#ifndef _CORE_TIMERLOOP_H_
#define _CORE_TIMERLOOP_H_
#include <memory>

namespace TimerHandler
{
    class ITimerQueue;
    class ITimer;
}

namespace Core {

class TimerLoop
{
    std::shared_ptr<TimerHandler::ITimerQueue> timerQueue_;
public:
    TimerLoop(std::shared_ptr<TimerHandler::ITimerQueue> timerQueue);
    void registerTimer(TimerHandler::ITimer* timer);
    void deRegisterTimer(uint64_t timerID);
    void runLoop();
};

}

#endif // _CORE_TIMERLOOP_H_
