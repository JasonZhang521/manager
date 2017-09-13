#ifndef _IPC_IPCSERVER_H_
#define _IPC_IPCSERVER_H_
#include "IIpcServer.h"
#include <memory>

namespace Ipc {

class IIpcConnectionServerStrategy;
class IpcServer : public IIpcServer
{
    std::shared_ptr<IIpcConnectionServerStrategy> strategy_;
public:
    IpcServer(std::shared_ptr<IIpcConnectionServerStrategy> strategy);
    ~IpcServer();
    virtual void startup();
    virtual void shutdown();
};

}
#endif // _IPC_IPCSERVER_H_
