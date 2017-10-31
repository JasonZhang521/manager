#include "SystemApi.h"
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

namespace PlatformWrapper {

SystemApi::SystemApi()
{
}

int SystemApi::getPid()
{
    return static_cast<int>(getpid());
}

}
