#include "IpcConnectionTcpServerStrategy.h"
#include "IIpcConnectionAcceptor.h"
#include "ITcpServer.h"
#include "IpSocketEndpoint.h"
#include "LoopMain.h"
#include "Trace.h"

namespace Ipc {
IpcConnectionTcpServerStrategy::IpcConnectionTcpServerStrategy(std::shared_ptr<IIpcConnectionAcceptor> connectionAcceptor,
                                                               std::shared_ptr<Network::ITcpServer> server)
    :connectionAcceptor_(connectionAcceptor)
    ,server_(server)
{
    if (!server_)
    {
        TRACE_ERROR("null Ipc server");
        throw std::invalid_argument("null Ipc server!");
    }
}

IpcConnectionTcpServerStrategy::IpcConnectionTcpServerStrategy(std::shared_ptr<Network::ITcpServer> server)
    :server_(server)
{
    if (!server_)
    {
        TRACE_ERROR("null Ipc server");
        throw std::invalid_argument("null Ipc server!");
    }
}

IpcConnectionTcpServerStrategy::~IpcConnectionTcpServerStrategy()
{
}

void IpcConnectionTcpServerStrategy::startup()
{
    TRACE_DEBUG("Tcp server init!");
    server_->init();
    TRACE_DEBUG("Tcp server bind!");
    server_->bind();
    int backlog = SOMAXCONN;
    TRACE_DEBUG("Tcp server start to listen!");
    server_->listen(backlog);
}

void IpcConnectionTcpServerStrategy::shutdown()
{
    TRACE_ENTER();
    server_->disconnect();
    server_->cleanup();
}
#include <iostream>
void IpcConnectionTcpServerStrategy::onAccept(int fd,
                      const Network::IpSocketEndpoint& localEndPoint,
                      const Network::IpSocketEndpoint& remoteEndPoint)
{
    TRACE_NOTICE("Client = " << remoteEndPoint << " connected to " << localEndPoint);
    connectionAcceptor_->onAccept(fd, localEndPoint, remoteEndPoint);
}

void  IpcConnectionTcpServerStrategy::setIpcConnectionAcceptor(std::shared_ptr<IIpcConnectionAcceptor> acceptor)
{
    TRACE_ENTER();
    connectionAcceptor_ = acceptor;
}


}
