#include "ShellCommandProcess.h"
#include "RemoveCharacter.h"
#include "Random.h"
#include "LoopMain.h"
#include "SystemErrorInfo.h"
#include "Trace.h"
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

namespace Environment {
ShellCommandProcess::ShellCommandProcess(const std::string& cmd)
    : TimerHandler::ITimer(100)
    , cmd_(cmd)
    , pid_(-1)
{

}

ShellCommandProcess::~ShellCommandProcess()
{

}

void ShellCommandProcess::execute()
{
#ifndef WIN32
    if ((pid_ = fork()) < 0)
    {
        TRACE_ERROR("fork failed: " << PlatformWrapper::GetLastErrorMessage() << std::endl);
    }
    // Child process
    else if (pid_ == 0)
    {
        if (outPutFile_.empty())
        {
            RemoveCharacter remover(' ', RemovePlace::LOCATION_FRONT | RemovePlace::LOCATION_MIDDLE | RemovePlace::LOCATION_END);
            const std::string filePrefix = remover(cmd_);
			Random random;
            outPutFile_ = "." + filePrefix + "." + random.generateUpLetterString(10);
        }
        const std::string cmd = cmd_ + " > " + outPutFile_;
        system(cmd.c_str());
    }
    else
    {
        Core::LoopMain::instance().registerTimer(this);
    }
#endif
}

void ShellCommandProcess::stop()
{

}

void ShellCommandProcess::onTime()
{
#ifndef WIN32
    int       status;
    pid_t ret = ::waitpid(pid_, &status, WNOHANG);

    if (ret > 0)
    {
        if (!WIFEXITED(status))
        {
            execute();
        }
    }
    else if (ret == -1)
    {
        resetTimer();
        Core::LoopMain::instance().registerTimer(this);
    }
#endif
}

std::ostream& ShellCommandProcess::operator<<(std::ostream& os)
{
    os << "["
       << "cmd=" << cmd_
       << ", outPutFile=" << outPutFile_
       << ", cmdOutput=";
    for (auto str : cmdOutput_)
    {
        os << str << std::endl;
    }
    os << "]";
    return os;
}

void ShellCommandProcess::getCmdOutPutFromFile()
{
    std::ifstream ifs(outPutFile_.c_str());

    if (!ifs.good())
    {
        TRACE_WARNING("Failed to open file: " << outPutFile_ << ", stop reading, try next time." << std::endl);
        return;
    }
    std::vector<std::string> lines;
    char buffer[512];
    while(ifs.good())
    {
        std::fill(buffer, buffer + 512, 0);
        ifs.getline(buffer, 512);
        std::stringstream ss;
        ss << buffer;
        std::string oneline = ss.str();
        lines.push_back(oneline);
    }

    if (!lines.empty())
    {
        cmdOutput_.swap(lines);
    }
}

}
