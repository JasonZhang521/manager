#ifndef _TIMEHANDLER_TIMESTAT_H_
#define _TIMEHANDLER_TIMESTAT_H_

#include <stdint.h>

class TimeStat
{
    uint64_t startTime_;
public:
    TimeStat();
    void restart();
    uint64_t getElapseTimeAsMilliSecond();
    uint64_t getElapseTimeAsSecond();
};

#endif // _TIMEHANDLER_TIMESTAT_H_
