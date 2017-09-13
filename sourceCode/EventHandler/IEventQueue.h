#ifndef IEVENTQUEUE_H
#define IEVENTQUEUE_H
#include <stdint.h>
#include <ostream>

namespace EventHandler {

class IEvent;

class IEventQueue
{
public:
    IEventQueue();
    virtual ~IEventQueue();
    virtual void addEvent(IEvent*) = 0;
    virtual void deleteEvent(uint64_t eventID) = 0;
    virtual void executeEvents(unsigned int executeTime) = 0;
    virtual std::ostream& operator<<(std::ostream& os) const = 0;
};

    std::ostream& operator<<(std::ostream& os, const IEventQueue* eventQueue);

}
#endif // IEVENTQUEUE_H
