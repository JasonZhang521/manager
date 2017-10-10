#ifndef _SYSTEMMONITOR_SYSTEMMONITORCONNECTIONRECEIVER_H_
#define _SYSTEMMONITOR_SYSTEMMONITORCONNECTIONRECEIVER_H_
#include "ISystemMonitorHandler.h"
#include "IIpcConnectionReceiver.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace IpcMessage {
class IIpcMessage;
}

namespace SystemMonitor {

class SystemMonitorConnectionReceiver : public Ipc::IIpcConnectionReceiver
{
    std::shared_ptr<ISystemMonitorHandler> monitorHandler_;
public:
    SystemMonitorConnectionReceiver(std::shared_ptr<ISystemMonitorHandler> monitorHandler);
    ~SystemMonitorConnectionReceiver();
protected:
    virtual void onConnect();
    virtual void onReceive(std::unique_ptr<IpcMessage::IIpcMessage> msg);
    virtual void onDisconnect();

private:
    void handleSystemMonitorMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg);
    void handleShellCommandMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg);

public:
     GETCLASSNAME(SystemMonitorConnectionReceiver)
};

}

#endif // _SYSTEMMONITOR_SYSTEMMONITORCONNECTIONRECEIVER_H_
