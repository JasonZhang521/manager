#ifndef IIPCCLIENT_H
#define IIPCCLIENT_H
#include <memory>

namespace IpcMessage
{
class IIpcMessage;
}

namespace Ipc {

class IIpcConnectionClientStrategy;

class IIpcClient
{
public:
    IIpcClient();
    ~IIpcClient();
    virtual void setConnectionStrategy(std::shared_ptr<IIpcConnectionClientStrategy> strategy) = 0;
    virtual void connect() = 0;
    virtual void send(IpcMessage::IIpcMessage& msg) = 0;
    virtual void disconnect() = 0;
};

}
#endif // IIPCCLIENT_H
