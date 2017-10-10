#ifndef UICLIENTPROCESS_H
#define UICLIENTPROCESS_H
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace IpcMessage {
class IIpcMessageQueue;
class IIpcMessage;
}

namespace std {
class thread;
}

namespace UiClient {
class UiClientProcess
{
    std::unique_ptr<std::thread> uiClientThread_;
    std::shared_ptr<IpcMessage::IIpcMessageQueue> ipcMessageSendQueue_;
    std::shared_ptr<IpcMessage::IIpcMessageQueue> ipcMessageReceiveQueue_;
public:
    UiClientProcess();
    ~UiClientProcess();
    void start();
    bool messageReceived();
    std::unique_ptr<IpcMessage::IIpcMessage> getOneMessage();
    void sendMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg);
private:
    void process();
public:
     GETCLASSNAME(UiClientProcess)
};
}
#endif // UICLIENTPROCESS_H
