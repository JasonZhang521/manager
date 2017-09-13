#ifndef IEVENT_H
#define IEVENT_H
#include <stdint.h>
#include <ostream>

namespace EventHandler {

enum class EventFlag
{
    Event_NoFlag,
    Event_IoRead,
    Event_IoWrite,
    Event_IoExcept
};

std::string EventFlagString(EventFlag flag);

class IEvent
{
    uint64_t eventId_;
public:
    IEvent();
    virtual ~IEvent();
    virtual uint64_t getEventId() const;
    virtual void run(EventFlag flag = EventFlag::Event_NoFlag) = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
};

std::ostream& operator<< (std::ostream& os, const IEvent* event);

}

#endif // IEVENT_H
