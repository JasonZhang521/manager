#include "EventLoop.h"
#include "IEventQueue.h"

namespace Core {

EventLoop::EventLoop(std::shared_ptr<EventHandler::IEventQueue> eventQueue)
    :eventQueue_(eventQueue)
{

}

void EventLoop::registerEvent(EventHandler::IEvent* event)
{
    if (eventQueue_)
    {
        eventQueue_->addEvent(event);
    }
}

void EventLoop::deRegisterEvent(uint64_t eventID)
{
    if (eventQueue_)
    {
        eventQueue_->deleteEvent(eventID);
    }
}

void EventLoop::runLoop(unsigned int executeTime)
{
    if (eventQueue_)
    {
        eventQueue_->executeEvents(executeTime);
    }
}

}
