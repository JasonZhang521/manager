#ifndef _IPC_IPCCLIENT_H_
#define _IPC_IPCCLIENT_H_
#include "IIpcClient.h"
#include "Component.h"
#include "Macro.h"
#include <memory>

namespace IpcMessage
{
class IIpcMessage;
}

namespace Ipc {

class IIpcConnectionClientStrategy;

class IpcClient : public IIpcClient
{
    std::shared_ptr<IIpcConnectionClientStrategy> strategy_;
public:
    IpcClient(std::shared_ptr<IIpcConnectionClientStrategy> strategy);
    IpcClient();
    virtual ~IpcClient();
private:   
    virtual void setConnectionStrategy(std::shared_ptr<IIpcConnectionClientStrategy> strategy);
    virtual void connect();
    virtual void send(IpcMessage::IIpcMessage& msg);
    virtual void disconnect();

public:
     GETCLASSNAME(IpcClient)
};

}

#endif // _IPC_IPCCLIENT_H_
