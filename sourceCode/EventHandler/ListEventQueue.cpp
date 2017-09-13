#include "ListEventQueue.h"
#include "IEvent.h"
#include "AppConst.h"
#include "Trace.h"
#include "TimeStat.h"
#include <memory>

namespace EventHandler {

ListEventQueue::ListEventQueue()
    :isExecuting_(false)
{
}

ListEventQueue::~ListEventQueue()
{
}

void ListEventQueue::addEvent(IEvent* event)
{
    if (!isExecuting_)
    {
        eventsList_.push_back(event);
    }
    else
    {
        eventCacheList_.push_back(EventCache(EventCache::Add, event->getEventId(), event));
    }
}

void ListEventQueue::deleteEvent(uint64_t eventId)
{
    if (!isExecuting_)
    {
        for (EventList::iterator it = eventsList_.begin(); it != eventsList_.end(); ++it)
        {
            if (eventId == (*it)->getEventId())
            {
                eventsList_.erase(it);
                return;
            }
        }
    }
    else
    {
        eventCacheList_.push_back(EventCache(EventCache::Delete, eventId, nullptr));
    }
}

void ListEventQueue::executeEvents(unsigned int executeTime)
{
    isExecuting_ = true;
    TimeStat totalStat;
    while (!eventsList_.empty())
    {
        TimeStat singleStat;
        std::unique_ptr<IEvent> event(eventsList_.front());
        eventsList_.pop_front();
        event->run();
        const uint64_t singleTimerElapse = singleStat.getElapseTimeAsMilliSecond();
        if (singleTimerElapse > MaxRunningDurationForSingleTimer)
        {
            TRACE_WARNING("Event is executing more than " << MaxRunningDurationForSingleEvent
                         << "ms, Timer Information" << event.get());
            break;
        }
        const uint64_t totalElapse = totalStat.getElapseTimeAsMilliSecond();
        if (totalElapse > executeTime)
        {
            break;
        }
    }

    const uint64_t totalElapse = totalStat.getElapseTimeAsMilliSecond();
    if (totalElapse > MaxRunningDurationForEventsInOneLoop)
    {
        TRACE_WARNING("Timers is executing more than " << MaxRunningDurationForTimersInOneLoop << "ms");
    }
    isExecuting_ = false;

    // event should be refresh
    refreshEvents();
}

void ListEventQueue::refreshEvents()
{
    if (isExecuting_)
    {
       TRACE_WARNING("Can not refresh events during execution!");
       return;
    }

    for (EventCacheList::iterator it = eventCacheList_.begin(); it != eventCacheList_.end(); ++it)
    {
        EventCache& eventCache = *it;
        if (eventCache.op_ == EventCache::Add)
        {
            addEvent(eventCache.event_);
        }
        else if (eventCache.op_ == EventCache::Delete)
        {
            deleteEvent(eventCache.eventId_);
        }
        else
        {
            TRACE_WARNING("unkown event operator: eventId = " << eventCache.eventId_ << ", operator = " << static_cast<int>(eventCache.op_));
        }
    }
    eventCacheList_.clear();
}

std::ostream& ListEventQueue::operator<<(std::ostream& os) const
{
    os << "[";
    for (EventList::const_iterator it = eventsList_.begin(); it != eventsList_.end(); ++it)
    {
       os << "event=" << *it;
    }
    os << "]";

    return os;
}

}
