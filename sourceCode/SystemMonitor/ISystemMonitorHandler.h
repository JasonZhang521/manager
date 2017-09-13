#ifndef _SYSTEMMONITOR_ISYSTEMMONITORHANDLER_H_
#define _SYSTEMMONITOR_ISYSTEMMONITORHANDLER_H_
#include <memory>

namespace Ipc {
class IIpcClient;
}

namespace SystemMonitor {
class ISystemMonitorHandler
{
public:
    ISystemMonitorHandler();
    ~ISystemMonitorHandler();
    virtual void setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient) = 0;
    virtual void reportSystemInfo() = 0;
    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void reStartup() = 0;
    virtual void onStartup() = 0;
    virtual void onShutdown() = 0;
};

}

#endif // _SYSTEMMONITOR_ISYSTEMMONITORHANDLER_H_
