#include "SystemTime.h"

#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

SystemTime::SystemTime()
{

}

uint64_t SystemTime::currentTimeStampAsSecond()
{
    milliseconds ms = duration_cast<seconds>(high_resolution_clock::now().time_since_epoch());
    return ms.count();
}

uint64_t SystemTime::currentTimeStampAsMillisecond()
{
   milliseconds ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
   return ms.count();
}

uint64_t SystemTime::expiredTimeStampAsMillisecond(uint32_t intervalAsMillisecond)
{
    milliseconds ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    return ms.count() + intervalAsMillisecond;
}
