#ifndef UICLIENTHANDLER_H
#define UICLIENTHANDLER_H
#include "IUiClientHandler.h"
#include "ITimer.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace Ipc {
class IIpcClient;
}

namespace UiClient {

class UiClientHandler : public IUiClientHandler
{
    class UiClientRestartTimer : public TimerHandler::ITimer
    {
        IUiClientHandler* handler_;
    public:
        UiClientRestartTimer(IUiClientHandler* handler);
        virtual void onTime();
        virtual std::ostream& operator<<(std::ostream& os);
    public:
         GETCLASSNAME(UiClientRestartTimer)
    };

    std::shared_ptr<Ipc::IIpcClient> ipcClient_;
    bool isStartup_;
    std::shared_ptr<UiClientRestartTimer> uiClientRestartTimer_;
public:
    UiClientHandler(std::shared_ptr<Ipc::IIpcClient> ipcClient);
    UiClientHandler();
    virtual ~UiClientHandler();
private:
    virtual void setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient);
    virtual void startup();
    virtual void shutdown();
    virtual void reStartup();
    virtual void onStartup();
    virtual void onShutdown();
public:
     GETCLASSNAME(UiClientHandler)
};

}
#endif // UICLIENTHANDLER_H
