#ifndef IUICLIENTHANDLER_H
#define IUICLIENTHANDLER_H
#include <memory>

namespace Ipc {
class IIpcClient;
}

namespace UiClient {
class IUiClientHandler
{
public:
    IUiClientHandler();
    virtual ~IUiClientHandler();
    virtual void setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient) = 0;
    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void reStartup() = 0;
    virtual void onStartup() = 0;
    virtual void onShutdown() = 0;
};

}

#endif // IUICLIENTHANDLER_H
