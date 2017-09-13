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
#include <memory>
#include <iostream>

namespace SystemMonitor {

SystemMonitorProcess::SystemMonitorProcess()
{
}

void SystemMonitorProcess::process()
{
    Network::IpAddresses ipAddresses = Network::NetworkEnv::getLocalIpAddress();
    for (auto ipAddress : ipAddresses)
    {
        std::cout << ipAddress << std::endl;
    }

    // Local and remote endpoint.
    Network::IpSocketEndpoint localEndpoint("0.0.0.0:0");
    Network::IpSocketEndpoint remoteEndpoint(std::string("127.0.0.1:23832"));
    //Network::IpSocketEndpoint remoteEndpoint(std::string("192.168.5.138:23832"));
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
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDf), 3600000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDf, commandDf);

        Environment::IShellCommand* commandDuHome =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::DiskUsageDuHome), 72000000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::DiskUsageDuHome, commandDuHome);

        Environment::IShellCommand* commandPsTop10CpuUsage =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::PsTop10CpuUsage), 5000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::PsTop10CpuUsage, commandPsTop10CpuUsage);

        Environment::IShellCommand* commandPsTop10MemoryUsage =
                new Environment::ShellCommandThread(Environment::ShellCommand::getCmdString(Environment::ShellCommandType::PsTop10MemoryUsage), 5000);
        Environment::Environment::instance().registerShellCmd(Environment::ShellCommandType::PsTop10MemoryUsage, commandPsTop10MemoryUsage);

    }

    systemMonitorHandler->startup();
    // run
    Core::LoopMain::instance().loopStart();
    std::cout << "run to the end----------------" << std::endl;
}

}

