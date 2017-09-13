#include "IIoEvent.h"

namespace Io {

IIoEvent::IIoEvent()
{
}

IIoEvent::~IIoEvent()
{
}

std::ostream& operator<< (std::ostream& os, const IIoEvent& event)
{
    return event.operator <<(os);
}

}
