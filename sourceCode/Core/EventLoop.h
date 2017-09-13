#ifndef _CORE_EVENTLOOP_H_
#define _CORE_EVENTLOOP_H_
#include <memory>

namespace EventHandler
{
    class IEventQueue;
    class IEvent;
}

namespace Core {

class EventLoop
{
    std::shared_ptr<EventHandler::IEventQueue> eventQueue_;
public:
    EventLoop(std::shared_ptr<EventHandler::IEventQueue> eventQueue);
    void registerEvent(EventHandler::IEvent* event);
    void deRegisterEvent(uint64_t eventID);
    void runLoop(unsigned int executeTime);
};

}

#endif // _CORE_EVENTLOOP_H_
