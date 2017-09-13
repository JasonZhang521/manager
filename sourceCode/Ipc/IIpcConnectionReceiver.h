#ifndef IIPCCONNECTIONRECEIVER_H
#define IIPCCONNECTIONRECEIVER_H
#include <memory>

namespace IpcMessage {
class IIpcMessage;
}

namespace Ipc {

class IIpcConnectionReceiver
{
public:
    IIpcConnectionReceiver();
    ~IIpcConnectionReceiver();
    virtual void onConnect() = 0;
    virtual void onReceive(std::unique_ptr<IpcMessage::IIpcMessage> msg) = 0;
    virtual void onDisconnect() = 0;
};

}

#endif // IIPCCONNECTIONRECEIVER_H
