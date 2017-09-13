#ifndef UIIPCCONNECTIONRECEIVER_H
#define UIIPCCONNECTIONRECEIVER_H
#include "IIpcConnectionReceiver.h"
#include "Component.h"
#include "Macro.h"

namespace IpcMessage {
class IIpcMessageQueue;
}

namespace UiClient {
class IUiClientHandler;

class UiIpcConnectionReceiver : public Ipc::IIpcConnectionReceiver
{
    std::shared_ptr<IUiClientHandler> uiClientHandler_;
    std::shared_ptr<IpcMessage::IIpcMessageQueue> ipcMessageReceiveQueue_;
public:
    UiIpcConnectionReceiver(std::shared_ptr<IUiClientHandler> uiClientHandler,
                            std::shared_ptr<IpcMessage::IIpcMessageQueue> ipcMessageReceiveQueue);
    virtual ~UiIpcConnectionReceiver();
    virtual void onConnect();
    virtual void onReceive(std::unique_ptr<IpcMessage::IIpcMessage> msg);
    virtual void onDisconnect();

private:
    void handleMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg);

public:
     GETCLASSNAME(UiIpcConnectionReceiver)
};

}

#endif // UIIPCCONNECTIONRECEIVER_H
