#include "UiClientHandler.h"
#include "IIpcClient.h"
#include "LoopMain.h"
#include "AppConst.h"
#include "Trace.h"

namespace UiClient {

UiClientHandler::UiClientRestartTimer::UiClientRestartTimer(IUiClientHandler* handler)
    : ITimer(UiClientRestartPeriod)
    , handler_(handler)
{

}

void UiClientHandler::UiClientRestartTimer::onTime()
{
    TRACE_DEBUG("Ui client re-start up!");
    handler_->startup();
}

std::ostream& UiClientHandler::UiClientRestartTimer::operator<<(std::ostream& os)
{
    TimerHandler::ITimer::print(os);
    return os;
}



UiClientHandler::UiClientHandler(std::shared_ptr<Ipc::IIpcClient> ipcClient)
    : ipcClient_(ipcClient)
    , isStartup_(false)
{

}

UiClientHandler::UiClientHandler()
{

}

UiClientHandler::~UiClientHandler()
{

}

void UiClientHandler::setIpcClient(std::shared_ptr<Ipc::IIpcClient> ipcClient)
{
    TRACE_ENTER();
    ipcClient_ = ipcClient;
}

void UiClientHandler::startup()
{
    TRACE_NOTICE("System monitor startup");
    ipcClient_->connect();
}

void UiClientHandler::shutdown()
{
    TRACE_NOTICE("System monitor shutdown");
    ipcClient_->disconnect();
}

void UiClientHandler::reStartup()
{
    TRACE_NOTICE("System monitor re-startup");
    if (!uiClientRestartTimer_)
    {
        uiClientRestartTimer_ = std::shared_ptr<UiClientRestartTimer>(new UiClientRestartTimer(this));
    }
    uiClientRestartTimer_->resetTimer();
    Core::LoopMain::instance().registerTimer(uiClientRestartTimer_.get());
}

void UiClientHandler::onStartup()
{
    TRACE_NOTICE("System monitor startup done!");
    isStartup_ = true;
}

void UiClientHandler::onShutdown()
{
    TRACE_NOTICE("System monitor shutdown done!");
    isStartup_ = false;
    reStartup();
}
}
