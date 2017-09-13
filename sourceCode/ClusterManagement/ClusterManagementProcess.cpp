#include "ClusterManagementProcess.h"
#include "ClusterMgtClientsManagement.h"
#include "ClusterMgtConnectionAcceptor.h"
#include "ClusterMgtController.h"
#include "IpcServerCreator.h"
#include "IIpcServer.h"
#include "IpSocketEndpoint.h"
#include "LoopMain.h"
#include "Environment.h"
#include "ShellCommandThread.h"
namespace ClusterManagement {
ClusterManagementProcess::ClusterManagementProcess()
{

}

void ClusterManagementProcess::process()
{
    // create the Cluster mananger control
    std::shared_ptr<IClusterMgtController> clusterMgtController(new ClusterMgtController());

    // create node server
    {
        // create the Ipc server, will set the tcp acceptor later
        Network::IpSocketEndpoint localEndpoint("127.0.0.1:23832");
        // create ipc acceptor
        ClusterMgtConnectionAcceptor* acceptorPtr = new ClusterMgtConnectionAcceptor(NodeType, clusterMgtController);
        std::shared_ptr<Ipc::IIpcConnectionAcceptor> acceptor(acceptorPtr);
        std::shared_ptr<Ipc::IIpcServer> ipcServer(Ipc::IpcServerCreator::CreateWithTcpServer(localEndpoint, acceptor));
        // add the client manger to the  mananger control
        std::unique_ptr<IClusterMgtClientsManagement> clientsManager(new ClusterMgtClientsManagment(NodeType, ipcServer));
        clusterMgtController->addClientManager(NodeType, std::move(clientsManager));
    }

    // create UI server
    {
        // create the Ipc server, will set the tcp acceptor later
        // Network::IpSocketEndpoint localEndpoint("127.0.0.1:23833");
        Network::IpSocketEndpoint localEndpoint("192.168.5.138:23833");
        // create ipc acceptor
        ClusterMgtConnectionAcceptor* acceptorPtr = new ClusterMgtConnectionAcceptor(UiType, clusterMgtController);
        std::shared_ptr<Ipc::IIpcConnectionAcceptor> acceptor(acceptorPtr);
        std::shared_ptr<Ipc::IIpcServer> ipcServer(Ipc::IpcServerCreator::CreateWithTcpServer(localEndpoint, acceptor));
        // add the client manger to the  mananger control
        std::unique_ptr<IClusterMgtClientsManagement> clientsManager(new ClusterMgtClientsManagment(UiType, ipcServer));
        clusterMgtController->addClientManager(UiType, std::move(clientsManager));
    }


    clusterMgtController->startup();

    // register the commands
    {
        Environment::IShellCommand* commandDf =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDf), 600000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDf, commandDf);

        Environment::IShellCommand* commandDuHome =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDuHome), 1200000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDuHome, commandDuHome);
    }
    // run
    Core::LoopMain::instance().loopStart();
}


}
