#ifndef _TIMERHANDLER_EVENTTIMER_H_
#define _TIMERHANDLER_EVENTTIMER_H_

#include "ITimer.h"
#include <stdint.h>
#include <memory>

namespace EventHandler {
    class IEvent;
}
namespace TimerHandler {

class EventTimer : public ITimer
{
    EventHandler::IEvent* event_;
public:
    EventTimer(uint32_t period, TimerType type, EventHandler::IEvent* event);
    virtual ~EventTimer();
protected:
    virtual void onTime();
    virtual std::ostream& operator<<(std::ostream& os);
};

}

#endif // _TIMERHANDLER_EVENTTIMER_H_
