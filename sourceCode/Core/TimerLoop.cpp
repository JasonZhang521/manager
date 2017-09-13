#include "TimerLoop.h"
#include "ITimerQueue.h"

namespace Core {

TimerLoop::TimerLoop(std::shared_ptr<TimerHandler::ITimerQueue> timerQueue)
    :timerQueue_(timerQueue)
{

}


void TimerLoop::registerTimer(TimerHandler::ITimer* timer)
{
    if (timerQueue_)
    {
        timerQueue_->addTimer(timer);
    }
}

void TimerLoop::deRegisterTimer(uint64_t timerID)
{
    if (timerQueue_)
    {
        timerQueue_->deleteTimer(timerID);
    }
}

void TimerLoop::runLoop()
{
    if (timerQueue_)
    {
        timerQueue_->executeTimers();
    }
}

}
