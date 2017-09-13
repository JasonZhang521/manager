#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

#include "stdint.h"

class SystemTime
{
public:
    SystemTime();
    static uint64_t currentTimeStampAsMillisecond();
    static uint64_t expiredTimeStampAsMillisecond(uint32_t intervalAsMillisecond);
};

#endif // SYSTEMTIME_H
