#include "SystemMonitorHandler.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcClient.h"
#include "CpuUsage.h"
#include "LoopMain.h"
#include "AppConst.h"
#include "Trace.h"

namespace SystemMonitor {

SystemMonitorHandler::SystemMonitorRestartTimer::SystemMonitorRestartTimer(ISystemMonitorHandler* handler)
    : ITimer(SystemMonitorPeriod)
    , handler_(handler)
{

}

void SystemMonitorHandler::SystemMonitorRestartTimer::onTime()
{
    TRACE_DEBUG("System monitor start up!");
    handler_->startup();
}

std::ostream& SystemMonitorHandler::SystemMonitorRestartTimer::operator<<(std::ostream& os)
{
    TimerHandler::ITimer::print(os);
    return os;
}

SystemMonitorHandler::SystemMonitorHandler(std::shared_ptr<Ipc::IIpcClient> ipcClient)
    : ipcClient_(ipcClient)
    , isStartup_(false)
{

}

SystemMonitorHandler::SystemMonitorHandler()
{

}

SystemMonitorHandler::~SystemMonitorHandler()
{

}

void SystemMonitorHandler::setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient)
{
    TRACE_ENTER();
    ipcClient_ = ipcClient;
}

void SystemMonitorHandler::reportSystemInfo()
{
    if (isStartup_)
    {
        Environment::SystemInfoBriefly info;
        info.update();
        SystemMonitorMessage::ComputerNodeInfoReport
                message(Environment::CpuUsageInfo(Environment::CpuUsage::instance().getCpuUsageEntrys()), info);
        message.setDestnation(Network::IpSocketEndpoint::BroadCastAddress);
        TRACE_DEBUG("report system information:" << message);
        ipcClient_->send(message);
    }
    else
    {
        TRACE_NOTICE("SystemMonitor is not start up!");
    }
}

void SystemMonitorHandler::startup()
{
    TRACE_NOTICE("System monitor startup");
    ipcClient_->connect();
}

void SystemMonitorHandler::shutdown()
{
    TRACE_NOTICE("System monitor shutdown");
    ipcClient_->disconnect();
}

void SystemMonitorHandler::reStartup()
{
    TRACE_NOTICE("System monitor re-startup");
    if (!systemMonitorRestartTimer_)
    {
        systemMonitorRestartTimer_ = std::shared_ptr<SystemMonitorRestartTimer>(new SystemMonitorRestartTimer(this));
    }
    systemMonitorRestartTimer_->resetTimer();
    Core::LoopMain::instance().registerTimer(systemMonitorRestartTimer_.get());
}

void SystemMonitorHandler::onStartup()
{
    TRACE_NOTICE("System monitor startup done!");
    isStartup_ = true;
}
void SystemMonitorHandler::onShutdown()
{
    TRACE_NOTICE("System monitor shutdown done!");
    isStartup_ = false;
    reStartup();
}

}
