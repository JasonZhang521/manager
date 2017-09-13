#include "EventTimer.h"
#include "IEvent.h"
#include <iostream>

namespace TimerHandler {

EventTimer::EventTimer(uint32_t period, TimerType type, EventHandler::IEvent* event)
    :ITimer(period, type)
    ,event_(event)
{
}

EventTimer::~EventTimer()
{
    std::cout << "~EventTimer" << std::endl;
}

void EventTimer::onTime()
{
    if (getTimerType() == TimerType::PeriodTimer)
    {
        resetTimer();
    }
    return event_->run();
}

std::ostream& EventTimer::operator<<(std::ostream& os)
{
    os << "[";
    TimerHandler::ITimer::print(os);
    os << ", event=" << event_
       << "]";

    return os;
}

}
