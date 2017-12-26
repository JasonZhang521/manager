#include "UnixProcess.h"
#include "FilePathHandler.h"
#include "SystemErrorInfo.h"
#include "Trace.h"
#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#endif

namespace ProcessManagementSupport
{

UnixProcess::UnixProcess(const std::string& executedBinaryPath)
    : executedBinaryPath_(executedBinaryPath)
{
}

UnixProcess::~UnixProcess()
{

}

void UnixProcess::startProcess()
{
    if (!FilePathHandler::isFileExist(executedBinaryPath_))
    {
        TRACE_ERROR("Can not fork the process:" << executedBinaryPath_ << ", the File is not exsited!");
        return;
    }
#ifndef _WIN32
    pid_t pid = fork();
    // parent process
    if (pid > 0)
    {
        pid_ = pid;
    }
    else if (pid == 0)
    {
        const std::string processName = FilePathHandler::getFileName(executedBinaryPath_);
        int ret = execl(executedBinaryPath_.c_str(), processName.c_str(), nullptr);
		if (ret)
		{
            TRACE_WARNING("start process failed: path=" << executedBinaryPath_
					                                    << ", processname=" << processName << ", error=" << PlatformWrapper::GetLastErrorMessage());
		}
        exit(0);
    }
    else
    {
        TRACE_ERROR("Can not fork the process:" << executedBinaryPath_);
    }
#endif
}

void UnixProcess::stopProcess()
{
#ifndef _WIN32
    if (pid_ > 0)
    {
        kill(pid_, 9);
    }
#endif
}

LPStatus UnixProcess::checkStatus()
{
    if (pid_ <= 0)
    {
        TRACE_NOTICE("process id=" << pid_ << " not started");
        return LPStatus::STOPPED;
    }
#ifndef _WIN32
    int status = -1;
    waitpid(pid_, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        status_ = LPStatus::STOPPED;
        TRACE_NOTICE("process id=" << pid_ << " exit normally, exit status =" << WEXITSTATUS(status));
        pid_ = -1;
    }
    else if (WIFSIGNALED(status))
    {
        status_ = LPStatus::STOPPED;
        TRACE_NOTICE("process id=" << pid_ << " exit by signal, signal is " << WTERMSIG(status));
        if (WCOREDUMP(status))
        {
            TRACE_NOTICE("process id=" << pid_ << "core dumped");
        }
        pid_ = -1;
    }
    else
    {
        status_ = LPStatus::RUNNING;
    }
#endif
    return status_;
}

}
