#include "IoLoop.h"
#include "ITimerQueue.h"
namespace Core {

IoLoop::IoLoop(std::shared_ptr<Io::IIoControl> ioControl)
    :ioControl_(ioControl)
{

}

void IoLoop::runLoop()
{

    if (ioControl_)
    {
        ioControl_->run();
    }
}

void IoLoop::registerIo(Io::IoFdType type, Io::IIoEvent* event)
{
    if (ioControl_)
    {
        ioControl_->registerIoFd(type, event);
    }
}

void IoLoop::deRegisterIo(Io::IoFdType type, int fd)
{
    if (ioControl_)
    {
        ioControl_->unRegisterIoFd(type, fd);
    }
}

}
