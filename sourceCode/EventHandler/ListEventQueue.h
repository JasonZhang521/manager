#ifndef _EVENTHANDLER_LISTEVENTQUEUE_H_
#define _EVENTHANDLER_LISTEVENTQUEUE_H_
#include "IEventQueue.h"
#include "Component.h"
#include "Macro.h"
#include <list>

namespace EventHandler {
class IEvent;

class ListEventQueue : public IEventQueue
{
    struct EventCache
    {
        enum Op{
            Add,
            Delete
        };
        Op op_;
        uint64_t eventId_;
        IEvent* event_;
        EventCache(Op op, uint64_t eventId, IEvent* event)
            :op_(op), eventId_(eventId), event_(event)
        {}
    };

    bool isExecuting_;
    using EventList = std::list<IEvent*>;
    EventList eventsList_;
    using EventCacheList = std::list<EventCache>;
    EventCacheList eventCacheList_;
public:
    ListEventQueue();
    virtual ~ListEventQueue();
protected:
    virtual void addEvent(IEvent*);
    virtual void deleteEvent(uint64_t eventId);
    virtual void executeEvents(unsigned int executeTime);
    virtual std::ostream& operator<<(std::ostream& os) const;
private:
    void refreshEvents();

public:
     GETCLASSNAME(ListEventQueue)
};

}

#endif // _EVENTHANDLER_EVENTQUEUE_H_
