#ifndef _CORE_IOLOOP_H_
#define _CORE_IOLOOP_H_
#include "IIoControl.h"
#include <memory>

namespace Io {
    class IIoControl;
}

namespace EventHandler
{
    class IEvent;
}

namespace Core {

class IoLoop
{
    std::shared_ptr<Io::IIoControl> ioControl_;
public:
    IoLoop(std::shared_ptr<Io::IIoControl> ioControl);
    void runLoop();
    void registerIo(Io::IoFdType type, Io::IIoEvent* event);
    void deRegisterIo(Io::IoFdType type, int fd);
};

}

#endif // _CORE_IOLOOP_H_
