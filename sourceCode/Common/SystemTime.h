#ifndef _TIMEHANDLER_SYSTEMTIME_H_
#define _TIMEHANDLER_SYSTEMTIME_H_

#include "stdint.h"


class SystemTime
{
public:
    SystemTime();
    static uint64_t currentTimeStampAsSecond();
    static uint64_t currentTimeStampAsMillisecond();
    static uint64_t expiredTimeStampAsMillisecond(uint32_t intervalAsMillisecond);
};

#endif // _TIMEHANDLER_SYSTEMTIME_H_
