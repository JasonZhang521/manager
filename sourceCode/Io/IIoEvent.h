#ifndef IIOEVENT_H
#define IIOEVENT_H
#include "IEvent.h"

namespace Io {

class IIoEvent : public EventHandler::IEvent
{
public:
    IIoEvent();
    virtual ~IIoEvent();
    virtual void run(EventHandler::EventFlag flag = EventHandler::EventFlag::Event_NoFlag) = 0;
    virtual std::ostream& operator<< (std::ostream& os) const = 0;
    virtual int getIoHandle() = 0;
};

std::ostream& operator<< (std::ostream& os, const IIoEvent& event);

}

#endif // IIOEVENT_H
