#include "IEvent.h"
#include "EventIdGenerator.h"
#include <string>

namespace EventHandler {

std::string EventFlagString(EventFlag flag)
{
    switch (flag) {
    case EventFlag::Event_IoRead:
        return std::string("IoRead");
        break;
    case EventFlag::Event_IoWrite:
        return std::string("IoWrite");
        break;
    case EventFlag::Event_IoExcept:
        return std::string("IoExcept");
        break;
    default:
        return std::string("None");
        break;
    }
}

IEvent::IEvent()
    :eventId_(EventHandler::EventIdGenerator::generateEventId())
{

}

IEvent::~IEvent()
{

}

uint64_t IEvent::getEventId() const
{
    return eventId_;
}

std::ostream& operator<< (std::ostream& os, const IEvent* event)
{
    event->operator <<(os);
    return os;
}

}
