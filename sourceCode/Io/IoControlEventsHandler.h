#ifndef _IO_IOCONTROLEVENT_H_
#define _IO_IOCONTROLEVENT_H_
#include "SocketWrapperDef.h"
#include "IIoControl.h"
#include "Component.h"
#include "Macro.h"
#include <map>
#include <list>

namespace Io {

class IoControlEventsHandler : public IIoControl
{
    struct IoEventCache
    {
        enum Op{
            Register,
            UnRegister
        };
        Op op_;
        int fd_;
        IIoEvent* event_;
        IoFdType type_;
        IoEventCache(Op op, int fd, IIoEvent* event, IoFdType type)
            :op_(op), fd_(fd), event_(event), type_(type)
        {}
    };

    struct IoFdEvent
    {
        IoFdEvent() : fdType(IoFdNoType), fdEvent(nullptr) {}
        IoFdEvent(IoFdType type, IIoEvent* event) : fdType(type), fdEvent(event) {}
        uint32_t fdType;
        IIoEvent* fdEvent;
    };

    SocketFdSet readFds_;
    SocketFdSet writeFds_;
    SocketFdSet exceptFds_;
    bool isRunning_;
    using IoFdEventMap = std::map<int, IoFdEvent>;
    IoFdEventMap fdEventMap_;
    using IoEventsCacheList = std::list<IoEventCache>;
    IoEventsCacheList ioEventsCacheList_;
public:
    IoControlEventsHandler();
    virtual ~IoControlEventsHandler();
protected:
    virtual void registerIoFd(IoFdType type, IIoEvent* event);
    virtual void unRegisterIoFd(IoFdType type, int fd);
    virtual void run();
    virtual std::ostream& operator<< (std::ostream& os) const;
private:
    void addToFdSet(int fd, uint32_t type);
    void removeFromFdSet(int fd, uint32_t type);

    void clearFdSet(uint32_t type);
    void clearAllFdSet();

    void refreshIoEvents();

public:
     GETCLASSNAME(IoControlEvent)
};

}

#endif // _IO_IOCONTROLEVENT_H_
