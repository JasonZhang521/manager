#include "SystemMonitorProcess.h"
#include "SystemInfoCollector.h"
#include "SystemMonitorHandler.h"
#include "SystemMonitorConnectionReceiver.h"
#include "SystemMonitorMessageFactory.h"
#include "IpcClient.h"
#include "IpcConnectionTcpClientStrategy.h"
#include "IpcClientCreator.h"
#include "IpcLayerMessageFactory.h"
#include "TcpClient.h"
#include "IpSocketEndpoint.h"
#include "EventTimer.h"
#include "LoopMain.h"
#include "NetworkEnv.h"
#include "IpAddress.h"
#include "Environment.h"
#include "ShellCommandThread.h"
#include "NetworkConfig.h"
#include "RemoveCharacter.h"
#include "CoredumpConfig.h"
#include "Configure.h"
#include "AppConst.h"
#include <memory>
#include <iostream>
#include <fstream>

namespace SystemMonitor {

SystemMonitorProcess::SystemMonitorProcess()
{
}

void SystemMonitorProcess::process()
{
    CoredumpConfig::LimitSet();
    Configure::getInstance().setTraceLogFilePath("/opt/HongClusterMgt/log/SystemMonitor.message.log");

    std::vector<std::string> nodeServerIpPorts = ConfigureManagement::NetworkConfig::getNodeServerIpPort();
    // Local and remote endpoint.
    Network::IpSocketEndpoint localEndpoint("0.0.0.0:0");
    Network::IpSocketEndpoint remoteEndpoint(nodeServerIpPorts[0]);
    // SystemMonitorHandler
    SystemMonitorHandler* systemMonitorHandlerPtr = new SystemMonitorHandler();
    std::shared_ptr<ISystemMonitorHandler> systemMonitorHandler(systemMonitorHandlerPtr);

    // SystemMonitorConnectionReceiver
    std::shared_ptr<SystemMonitorConnectionReceiver>
            systemMonitorConnectionReceiver(new SystemMonitorConnectionReceiver(systemMonitorHandler));

    IpcMessageFactories factories;
    // System monitor factory
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new SystemMonitorMessage::SystemMonitorMessageFactory()));
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new IpcMessage::IpcLayerMessageFactory()));

    Ipc::IIpcClient* ipcClientPtr = Ipc::IpcClientCreator::CreateWithTcpClientStrategy(localEndpoint, remoteEndpoint, systemMonitorConnectionReceiver, factories);
    std::shared_ptr<Ipc::IIpcClient> ipcClient(ipcClientPtr);

    systemMonitorHandlerPtr->setIpcClient(ipcClient);

    // SystemInfoCollector
    SystemInfoCollector* systemInfoCollectorPtr = new SystemInfoCollector(systemMonitorHandler);
    std::shared_ptr<SystemInfoCollector> systemInfoCollector(systemInfoCollectorPtr);

    // EventTimer
    TimerHandler::EventTimer* timerPtr = new TimerHandler::EventTimer(5000, TimerHandler::TimerType::PeriodTimer, systemInfoCollectorPtr);
    std::unique_ptr<TimerHandler::EventTimer> eTimer(timerPtr);

    Core::LoopMain::instance().registerTimer(timerPtr);

    // register the commands
    {
        Environment::IShellCommand* commandDf =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDf), DfCommandPeriod);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDf, commandDf);

     //   Environment::IShellCommand* commandDuHome =
       //         new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDuHome), DuCommandPeriod);
      //  Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDuHome, commandDuHome);

        Environment::IShellCommand* commandPsTop10CpuUsage =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::PsTop10CpuUsage), 5000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::PsTop10CpuUsage, commandPsTop10CpuUsage);

        Environment::IShellCommand* commandPsTop10MemoryUsage =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::PsTop10MemoryUsage), 5000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::PsTop10MemoryUsage, commandPsTop10MemoryUsage);

        Environment::IShellCommand* commandNvidiaSmiGpu =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::NvidiaSmiGpu), 3600000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::NvidiaSmiGpu, commandNvidiaSmiGpu);

        Environment::IShellCommand* commandInfiniBandStat =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::InfiniBandStat), 3600000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::InfiniBandStat, commandInfiniBandStat);

    }

    systemMonitorHandler->startup();
    // run
    Core::LoopMain::instance().loopStart();
    std::cout << "run to the end----------------" << std::endl;
}

}

