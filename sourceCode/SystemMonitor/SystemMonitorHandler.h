#ifndef _SYSTEMMONITOR_SYSTEMMONITORHANDLER_H_
#define _SYSTEMMONITOR_SYSTEMMONITORHANDLER_H_
#include "ISystemMonitorHandler.h"
#include "SystemInfoCollector.h"
#include "ITimer.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace Ipc {
    class IIpcClient;
}

namespace SystemMonitor {

class SystemMonitorHandler : public ISystemMonitorHandler
{
    class SystemMonitorRestartTimer : public TimerHandler::ITimer
    {
        ISystemMonitorHandler* handler_;
    public:
        SystemMonitorRestartTimer(ISystemMonitorHandler* handler);
        virtual void onTime();
        virtual std::ostream& operator<<(std::ostream& os);
    public:
         GETCLASSNAME(SystemMonitorRestartTimer)
    };

    std::shared_ptr<Ipc::IIpcClient> ipcClient_;
    bool isStartup_;
    std::shared_ptr<SystemMonitorRestartTimer> systemMonitorRestartTimer_;
public:
    SystemMonitorHandler(std::shared_ptr<Ipc::IIpcClient> ipcClient);
    SystemMonitorHandler();
    ~SystemMonitorHandler();
    virtual void setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient);
private:
    virtual void reportSystemInfo();
    virtual void startup();
    virtual void shutdown();
    virtual void reStartup();
    virtual void onStartup();
    virtual void onShutdown();

public:
     GETCLASSNAME(SystemMonitorHandler)
};

}

#endif // _SYSTEMMONITOR_SYSTEMMONITORHANDLER_H_
