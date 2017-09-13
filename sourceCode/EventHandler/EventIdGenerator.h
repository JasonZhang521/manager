#ifndef _EVENTHANDLER_EVENTIDGENERATOR_H_
#define _EVENTHANDLER_EVENTIDGENERATOR_H_
#include <stdint.h>

namespace EventHandler {

class EventIdGenerator
{
    static uint64_t eventId_;
public:
    EventIdGenerator();
    static uint64_t generateEventId();
};

}

#endif // _EVENTHANDLER_EVENTIDGENERATOR_H_
