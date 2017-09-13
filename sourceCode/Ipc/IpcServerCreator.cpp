#include "IpcServerCreator.h"
#include "IpcConnectionTcpServerStrategy.h"
#include "TcpServer.h"
#include "IpcServer.h"
#include "LoopMain.h"
namespace Ipc {
IpcServerCreator::IpcServerCreator()
{

}

IIpcServer* IpcServerCreator::CreateWithTcpServer(const Network::IpSocketEndpoint& localEndPoint,
                                                  std::shared_ptr<Ipc::IIpcConnectionAcceptor> ipcConnectionAcceptor)
{
    // create the Ipc server, will set the tcp acceptor later
    Network::TcpServer* tcpServerPtr = new Network::TcpServer(localEndPoint);
    std::shared_ptr<Network::ITcpServer> tcpServer(tcpServerPtr);

    // create the Tcp server strategy,  this is the Tcp acceptor also
    Ipc::IpcConnectionTcpServerStrategy* strategyPtr = new Ipc::IpcConnectionTcpServerStrategy(tcpServer);
    std::shared_ptr<Ipc::IpcConnectionTcpServerStrategy> strategy(strategyPtr);

    // set the Tcp acceptor
    tcpServer->setConnectionAcceptor(strategy);

    // create the Ipc server, will set the ipc acceptor later
    Ipc::IIpcServer* ipcServerPtr = new Ipc::IpcServer(strategy);

    // set the ipc acceptor
    strategyPtr->setIpcConnectionAcceptor(ipcConnectionAcceptor);

    Core::LoopMain::instance().registerIo(Io::IoFdType::IoFdRead, tcpServerPtr);

    return ipcServerPtr;
}
}
