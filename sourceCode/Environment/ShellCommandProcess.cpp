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

std::string ShellCommandProcess::MagicString("EGHDVYHEJHDRRHSFRH");

ShellCommandProcess::ShellCommandProcess(const std::string& cmd, bool oneTimeCommand)
    : TimerHandler::ITimer(100)
    , cmd_(cmd)
    , oneTimeCommand_(oneTimeCommand)
    , pid_(-1)
{

}

ShellCommandProcess::~ShellCommandProcess()
{

}

void ShellCommandProcess::execute()
{
    if (outPutFile_.empty() && !oneTimeCommand_)
    {
        RemoveCharacter remover(' ', RemovePlace::LOCATION_FRONT | RemovePlace::LOCATION_MIDDLE | RemovePlace::LOCATION_END);
        std::string filePrefix = remover.removeMultiCh(cmd_, "\t \\/-,|=");
        filePrefix = MagicString + "." + filePrefix;
        Random random;
        outPutFile_ = "." + filePrefix + "." + random.generateUpLetterString(10);
        // delete the previous files
        std::string deletePreviousfiles = std::string("rm .") + filePrefix + std::string("*");
        system(deletePreviousfiles.c_str());
    }

#ifndef WIN32
    if ((pid_ = fork()) < 0)
    {
        TRACE_ERROR("fork failed: " << PlatformWrapper::GetLastErrorMessage() << std::endl);
    }
    // Child process
    else if (pid_ == 0)
    {
        if (oneTimeCommand_)
        {
            system(cmd_.c_str());
        }
        else
        {
            const std::string cmd = cmd_ + " > " + outPutFile_;
            system(cmd.c_str());
        }
    }
    else
    {
        if (!oneTimeCommand_)
        {
            Core::LoopMain::instance().registerTimer(this);
        }
    }
#endif
}

void ShellCommandProcess::stop()
{

}

bool ShellCommandProcess::isInactive()
{
    return false;
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
