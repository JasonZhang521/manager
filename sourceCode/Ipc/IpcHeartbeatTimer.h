#ifndef IPCHEARTBEATTIMER_H
#define IPCHEARTBEATTIMER_H
#include "ITimer.h"
#include "Component.h"
#include "Macro.h"

namespace Ipc {

class IIpcConnectionClientStrategy;
class IpcHeartbeatTimer : public TimerHandler::ITimer
{
    IIpcConnectionClientStrategy* clientStrategy_;
public:
    IpcHeartbeatTimer(IIpcConnectionClientStrategy* clientStrategy);
    virtual ~IpcHeartbeatTimer();
    virtual void onTime();
    virtual std::ostream& operator<<(std::ostream& os);

public:
     GETCLASSNAME(IpcConnectionTimer)
};

}

#endif // IPCHEARTBEATTIMER_H
