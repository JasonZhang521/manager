#include "IpcServer.h"
#include "IIpcConnectionServerStrategy.h"

namespace Ipc {

IpcServer::IpcServer(std::shared_ptr<IIpcConnectionServerStrategy> strategy)
    :strategy_(strategy)
{

}

IpcServer::~IpcServer()
{

}

void IpcServer::startup()
{
    strategy_->startup();
}

void IpcServer::shutdown()
{
    strategy_->shutdown();
}

}
