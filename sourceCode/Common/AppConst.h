#ifndef _COMMON_APPCONST_H_
#define _COMMON_APPCONST_H_
#include <stdint.h>

const uint64_t MaxRunningDurationForSingleTimer = 50; //ms
const uint64_t MaxRunningDurationForTimersInOneLoop = 500; //ms

const uint64_t MaxRunningDurationForSingleEvent = 50; //ms
const uint64_t MaxRunningDurationForEventsInOneLoop = 500; //ms

const int32_t MaxRunningTimeInOneLoop = 2000; //ms

const int32_t ConnectionTimeout = 30000; //ms
const int32_t HeartbeatPeriod = 15000;  //ms
const int32_t SystemMonitorPeriod = 3000; //ms
const int32_t UiClientRestartPeriod = 3000; //ms

const int32_t DfCommandPeriod = 3600000; // 1 hour
const int32_t DuCommandPeriod = 3600000 * 24;

#endif // _COMMON_APPCONST_H_
