#ifndef _TIMERHANDLER_TIMERIDGENERATOR_H_
#define _TIMERHANDLER_TIMERIDGENERATOR_H_
#include <stdint.h>

namespace TimerHandler {

class TimerIdGenerator
{
    static uint64_t timerId;

private:
    TimerIdGenerator();
public:
    static uint64_t generateTimerId();
};

}

#endif // _TIMERHANDLER_TIMERIDGENERATOR_H_
