#ifndef _CORE_LOOPMAIN_H_
#define _CORE_LOOPMAIN_H_
#include "EventLoop.h"
#include "IoLoop.h"
#include "TimerLoop.h"
#include <memory>
#include "Component.h"
#include "Macro.h"

namespace TimerHandler {
class ITimer;
}

namespace EventHandler {
class IEvent;
}
namespace Core {

class LoopMain
{
    EventLoop eventLoop_;
    TimerLoop timeLoop_;
    IoLoop ioLoop_;
    unsigned int timeExcuteInOneLoop;
    bool stop_;
public:
    LoopMain();
    void registerTimer(TimerHandler::ITimer* timer);
    void deRegisterTimer(uint64_t timerID);
    void registerEvent(EventHandler::IEvent* event);
    void deRegisterEvent(uint64_t eventID);
    void registerIo(Io::IoFdType type, Io::IIoEvent* IEvent);
    void deRegisterIo(Io::IoFdType type, int fd);
    void loopStart();
    void loopStop();

public:
    static LoopMain& instance();

public:
    GETCLASSNAME(LoopMain)
};

}

#endif // _CORE_LOOPMAIN_H_
