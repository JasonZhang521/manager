#include "LoopMain.h"
#include "ListEventQueue.h"
#include "ListTimerQueue.h"
#include "IoControlEventsHandler.h"
#include "AppConst.h"
#include "Singleton.h"
#include "TimeStat.h"
#include "Sleep.h"
#include "Trace.h"

namespace Core {
LoopMain::LoopMain()
    : eventLoop_(std::shared_ptr<EventHandler::IEventQueue>(new EventHandler::ListEventQueue()))
    , timeLoop_(std::shared_ptr<TimerHandler::ITimerQueue>(new TimerHandler::ListTimerQueue))
    , ioLoop_(std::shared_ptr<Io::IIoControl>(new Io::IoControlEventsHandler()))
    , timeExcuteInOneLoop(MaxRunningTimeInOneLoop)
    , stop_(false)
{

}

void LoopMain::registerTimer(TimerHandler::ITimer* timer)
{
    timeLoop_.registerTimer(timer);
}

void LoopMain::deRegisterTimer(uint64_t timerID)
{
    timeLoop_.deRegisterTimer(timerID);
}

void LoopMain::registerEvent(EventHandler::IEvent* event)
{
    eventLoop_.registerEvent(event);
}

void LoopMain::deRegisterEvent(uint64_t eventID)
{
    eventLoop_.deRegisterEvent(eventID);
}

void LoopMain::registerIo(Io::IoFdType type, Io::IIoEvent* event)
{
    ioLoop_.registerIo(type, event);
}

void LoopMain::deRegisterIo(Io::IoFdType type, int fd)
{
    ioLoop_.deRegisterIo(type, fd);
}

void LoopMain::loopStart()
{
    stop_ = false;
    while (!stop_)
    {
        int32_t remainingTime = MaxRunningTimeInOneLoop;
        TimeStat timeStat;
		TRACE_DEBUG3("Run IO loop!");
        ioLoop_.runLoop();
        remainingTime = remainingTime - timeStat.getElapseTimeAsMilliSecond();
		TRACE_DEBUG3("Run event loop!");
        eventLoop_.runLoop(666);
        remainingTime = remainingTime - timeStat.getElapseTimeAsMilliSecond();
		TRACE_DEBUG3("Run timer loop!");
        timeLoop_.runLoop();
        remainingTime = remainingTime - timeStat.getElapseTimeAsMilliSecond();

        if (remainingTime > 0)
        {
            if (remainingTime < 50)
            {
                System::Sleep(remainingTime);
            }
            else
            {
                System::Sleep(50);
            }
        }
    }

}

void LoopMain::loopStop()
{
    stop_ = true;
}

LoopMain& LoopMain::instance()
{
    static std::unique_ptr<LoopMain> instance(new LoopMain());
    return *instance;
}

}
