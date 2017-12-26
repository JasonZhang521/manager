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
#include "NetworkConfig.h"
#include "CoredumpConfig.h"
#include "Configure.h"
#include "AppConst.h"

namespace ClusterManagement {
ClusterManagementProcess::ClusterManagementProcess()
{

}

void ClusterManagementProcess::process()
{
    CoredumpConfig::LimitSet();
    Configure::getInstance().setTraceLogFilePath("/opt/HongClusterMgt/log/ClusterManagement.message.log");

    // create the Cluster mananger control
    std::shared_ptr<IClusterMgtController> clusterMgtController(new ClusterMgtController());

    std::vector<std::string> nodeServerIpPorts = ConfigureManagement::NetworkConfig::getNodeServerIpPort();
    std::vector<std::string> uiServerIpPorts = ConfigureManagement::NetworkConfig::getUiServerIpPort();

    // create node server
    {
        // create the Ipc server, will set the tcp acceptor later
        Network::IpSocketEndpoint localEndpoint(nodeServerIpPorts[0]);
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
        Network::IpSocketEndpoint localEndpoint(uiServerIpPorts[0]);
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
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDf), DfCommandPeriod);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDf, commandDf);

        //Environment::IShellCommand* commandDuHome =
          //      new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDuHome), DuCommandPeriod);
     //   Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDuHome, commandDuHome);
    }
    // run
    Core::LoopMain::instance().loopStart();
}


}
