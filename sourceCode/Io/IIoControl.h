#ifndef _IO_IIOCONTROL_H_
#define _IO_IIOCONTROL_H_
#include <ostream>

namespace Io {

class IIoEvent;

enum IoFdType
{
    IoFdNoType = 0,
    IoFdRead = 1,
    IoFdWrite = 1 << 2,
    IoFdExcept = 1 << 3,
    IoFdAll = IoFdRead | IoFdWrite | IoFdExcept
};

class IIoControl
{
public:
    IIoControl();
    virtual ~IIoControl();
    virtual void registerIoFd(IoFdType type, IIoEvent* IEvent) = 0;
    virtual void unRegisterIoFd(IoFdType type, int fd) = 0;
    virtual void run() = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
};

}

#endif // _IO_IIOCONTROL_H_
