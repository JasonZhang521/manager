#include "IpcClient.h"
#include "IIpcMessage.h"
#include "IIpcConnectionClientStrategy.h"
#include "Trace.h"

namespace Ipc {

IpcClient::IpcClient(std::shared_ptr<IIpcConnectionClientStrategy> strategy)
    :strategy_(strategy)
{

}

IpcClient::IpcClient()
{

}

IpcClient::~IpcClient()
{

}

void IpcClient::setConnectionStrategy(std::shared_ptr<IIpcConnectionClientStrategy> strategy)
{
    TRACE_ENTER();
    strategy_ = strategy;
}

void IpcClient::connect()
{
    TRACE_ENTER();
    strategy_->connect();
}

void IpcClient::send(IpcMessage::IIpcMessage& msg)
{
    TRACE_ENTER();
    strategy_->send(msg);
}

void IpcClient::disconnect()
{
    TRACE_ENTER();
    strategy_->disconnect();
}

}
