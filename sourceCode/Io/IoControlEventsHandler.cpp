#include "IoControlEventsHandler.h"
#include "SocketWrapper.h"
#include "EventIdGenerator.h"
#include "IIoEvent.h"
#include "Generic.h"
#include <string>
#include "Trace.h"

namespace Io {

IoControlEventsHandler::IoControlEventsHandler()
{
    PlatformWrapper::FdZero(&readFds_);
    PlatformWrapper::FdZero(&writeFds_);
    PlatformWrapper::FdZero(&exceptFds_);
}

IoControlEventsHandler::~IoControlEventsHandler()
{
    PlatformWrapper::FdZero(&readFds_);
    PlatformWrapper::FdZero(&writeFds_);
    PlatformWrapper::FdZero(&exceptFds_);
}

void IoControlEventsHandler::registerIoFd(IoFdType type, IIoEvent* event)
{
    int fd = event->getIoHandle();
    TRACE_NOTICE("fd = " << fd << ", type = " << type << ", event = " << event);
    if (!isRunning_)
    {
        IoFdEventMap::iterator it = fdEventMap_.find(fd);
        if (it != fdEventMap_.end())
        {
            IoFdEvent& event = it->second;
            if ((event.fdType & type) != IoFdType::IoFdNoType)
            {
                TRACE_NOTICE("fd = " << fd << ", IoFdType = " << static_cast<int>(type) << " has already registered!");
                return;
            }
            else
            {
                event.fdType = (event.fdType | type);
                addToFdSet(fd, type);
            }
        }
        else
        {
            fdEventMap_.insert(std::pair<int, IoFdEvent>(fd, IoFdEvent(type, event)));
            addToFdSet(fd, type);
        }
    }
    else
    {
        ioEventsCacheList_.push_back(IoEventCache(IoEventCache::Register, fd, event, type));
    }
}

void IoControlEventsHandler::unRegisterIoFd(IoFdType type, int fd)
{
    TRACE_NOTICE("fd = " << fd << ", type = " << static_cast<int>(type));
    if (!isRunning_)
    {
        IoFdEventMap::iterator it = fdEventMap_.find(fd);
        if (it != fdEventMap_.end())
        {
            IoFdEvent& event = it->second;
            event.fdType &= ~type;
            if (event.fdType == IoFdType::IoFdNoType)
            {
                fdEventMap_.erase(it);
            }

            removeFromFdSet(fd, type);
        }
    }
    else
    {
        ioEventsCacheList_.push_back(IoEventCache(IoEventCache::UnRegister, fd, nullptr, type));
    }
}

void IoControlEventsHandler::run()
{
    TRACE_ENTER();
    if (fdEventMap_.empty())
    {
        TRACE_DEBUG3("No fd to be handled!");
        refreshIoEvents();
        return;
    }

    isRunning_ = true;

    clearAllFdSet();
    IoFdEventMap::iterator it = fdEventMap_.begin();
    for (; it != fdEventMap_.end(); ++it)
    {
        int fd = it->first;
        const IoFdEvent& event = it->second;
        addToFdSet(fd, event.fdType);
    }

    IoFdEventMap::reverse_iterator rit = fdEventMap_.rbegin();
    int maxFdNum = rit->first + 1;
    SocketTimeVal timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500;
    PlatformWrapper::Select(maxFdNum, &readFds_, &writeFds_, &exceptFds_, &timeout);

    for (; rit != fdEventMap_.rend(); ++rit)
    {
        int fd = rit->first;
        IIoEvent* event = rit->second.fdEvent;
        uint32_t fdType = rit->second.fdType;

        if (fdType & IoFdType::IoFdRead && PlatformWrapper::FdIsSet(fd, &readFds_))
        {
            event->run(EventHandler::EventFlag::Event_IoRead);
        }

        if (fdType & IoFdType::IoFdWrite && PlatformWrapper::FdIsSet(fd, &writeFds_))
        {
            event->run(EventHandler::EventFlag::Event_IoWrite);
        }

        if (fdType & IoFdType::IoFdExcept && PlatformWrapper::FdIsSet(fd, &exceptFds_))
        {
            event->run(EventHandler::EventFlag::Event_IoExcept);
        }
    }

    isRunning_ = false;

    refreshIoEvents();
}

std::ostream& IoControlEventsHandler::operator<< (std::ostream& os) const
{
    os << "[";

    for (IoFdEventMap::const_iterator it = fdEventMap_.cbegin(); it != fdEventMap_.cend(); ++it)
    {
        os << "fd=" << it->first << ", eventType=" << it->second.fdType << ", event=" << it->second.fdEvent;
    }
    os << "]";

    return os;
}

void IoControlEventsHandler::addToFdSet(int fd, uint32_t type)
{
    if (type & IoFdType::IoFdRead)
    {
        PlatformWrapper::FdSet(fd, &readFds_);
    }

    if(type & IoFdType::IoFdWrite)
    {
        PlatformWrapper::FdSet(fd, &writeFds_);
    }

    if (type & IoFdType::IoFdExcept)
    {
        PlatformWrapper::FdSet(fd, &exceptFds_);
    }
}

void IoControlEventsHandler::clearFdSet(uint32_t type)
{
    if (type & IoFdType::IoFdRead)
    {
        PlatformWrapper::FdZero(&readFds_);
    }

    if(type & IoFdType::IoFdWrite)
    {
        PlatformWrapper::FdZero(&writeFds_);
    }

    if (type & IoFdType::IoFdExcept)
    {
        PlatformWrapper::FdZero(&exceptFds_);
    }
}

void IoControlEventsHandler::clearAllFdSet()
{
    clearFdSet(IoFdType::IoFdRead | IoFdType::IoFdWrite | IoFdType::IoFdExcept);
}

void IoControlEventsHandler::removeFromFdSet(int fd, uint32_t type)
{
    if (type & IoFdType::IoFdRead)
    {
        PlatformWrapper::FdClear(fd, &readFds_);
    }

    if(type & IoFdType::IoFdWrite)
    {
        PlatformWrapper::FdClear(fd, &writeFds_);
    }

    if (type & IoFdType::IoFdExcept)
    {
        PlatformWrapper::FdClear(fd, &exceptFds_);
    }
}

void IoControlEventsHandler::refreshIoEvents()
{
    if (isRunning_)
    {
       TRACE_WARNING("Can not refresh ioEvent during running!");
       return;
    }

    for (IoEventsCacheList::iterator it = ioEventsCacheList_.begin(); it != ioEventsCacheList_.end(); ++it)
    {
        IoEventCache& ioEventCache = *it;
        if (ioEventCache.op_ == IoEventCache::Register)
        {
            registerIoFd(ioEventCache.type_, ioEventCache.event_);
        }
        else if (ioEventCache.op_ == IoEventCache::UnRegister)
        {
            unRegisterIoFd(ioEventCache.type_, ioEventCache.fd_);
        }
        else
        {
            TRACE_WARNING("unkown event operator: eventId = " << ioEventCache.fd_ << ", operator = " << static_cast<int>(ioEventCache.op_));
        }
    }
    ioEventsCacheList_.clear();
}

}
