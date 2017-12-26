#include "CoredumpConfig.h"
#ifndef _WIN32
#include <sys/time.h>
#include <sys/resource.h>
#endif
CoredumpConfig::CoredumpConfig()
{

}

void CoredumpConfig::LimitSet()
{
#ifndef _WIN32
    struct rlimit rl;
    rl.rlim_cur = 1024 * 1024 * 100;
    rl.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &rl);
#endif
}
