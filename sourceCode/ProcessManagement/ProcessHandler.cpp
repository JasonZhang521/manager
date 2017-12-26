#include "ProcessHandler.h"
#include "UnixProcess.h"

namespace ProcessManagement {
ProcessHandler::ProcessHandler(const std::string& executedFilePath)
    : ITimer(500, TimerHandler::TimerType::PeriodTimer)
    , process_(new ProcessManagementSupport::UnixProcess(executedFilePath))
{
}

ProcessHandler::~ProcessHandler()
{

}

void ProcessHandler::onTime()
{
    ProcessManagementSupport::LPStatus status = process_->checkStatus();
    if (ProcessManagementSupport::LPStatus::STOPPED == status)
    {
        process_->startProcess();
    }
}

std::ostream& ProcessHandler::operator<<(std::ostream& os)
{
    return os;
}

}
