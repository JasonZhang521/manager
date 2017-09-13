#include "IEventQueue.h"
namespace EventHandler {

IEventQueue::IEventQueue()
{

}

IEventQueue::~IEventQueue()
{

}

std::ostream& operator<<(std::ostream& os, const IEventQueue* eventQueue)
{
    eventQueue->operator <<(os);
    return os;
}

}
