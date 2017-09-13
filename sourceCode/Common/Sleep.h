#ifndef SLEEP_H
#define SLEEP_H

#ifdef WIN32
#include <windows.h>
class System
{
public:
    inline static void Sleep(int milliSecond)
    {
        ::Sleep(milliSecond);
    }
};

#else
#include <unistd.h>
class System
{
public:
    inline static void Sleep(int milliSecond)
    {
        ::usleep(milliSecond * 1000);
    }
};
#endif

#endif // SLEEP_H
