#ifndef IPCCONNECTIONTIMER_H
#define IPCCONNECTIONTIMER_H
#include "ITimer.h"
#include "Component.h"
#include "Macro.h"

namespace Ipc {
class IIpcConnectionClientStrategy;
class IIpcConnectionReceiver;

class IpcConnectionTimer : public TimerHandler::ITimer
{
    IIpcConnectionClientStrategy* clientStrategy_;
    IIpcConnectionReceiver* connectionReceiver_;
public:
    IpcConnectionTimer(IIpcConnectionClientStrategy* clientStrategy,
                       IIpcConnectionReceiver* connectionReceiver);
    virtual ~IpcConnectionTimer();
    virtual void onTime();
    virtual std::ostream& operator<<(std::ostream& os);

public:
     GETCLASSNAME(IpcConnectionTimer)
};

}

#endif // IPCCONNECTIONTIMER_H
