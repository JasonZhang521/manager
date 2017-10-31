#include "ShellCommandThread.h"
#include "RemoveCharacter.h"
#include "Random.h"
#include "LoopMain.h"
#include "SystemErrorInfo.h"
#include "Lock.h"
#include "SystemApi.h"
#include "Trace.h"
#include "Generic.h"
#include <thread>

namespace Environment {

std::string ShellCommandThread::ExcuteStateToString(ExcuteState state)
{
    switch (state) {
    case ExcuteState::Command_Start:
        return std::string("Command_Start");
    case ExcuteState::Command_Stop:
        return std::string("Command_Stop");
    case ExcuteState::OutPut_Retreived:
        return std::string("OutPut_Retreived");
    case ExcuteState::Thread_Stop:
        return std::string("Thread_Stop");
    case ExcuteState::InActive:
        return std::string("InActive");
    default:
        return std::string("Invalid_State");
    }
}

std::string ShellCommandThread::MagicString("EGHDVYHEJHDRRHSFRH"); 
ShellCommandThread::ShellCommandThread(const std::string& cmd, uint32_t timeout)
    : TimerHandler::ITimer(timeout)
    , cmd_(cmd)
    , excuteState_(ExcuteState::InActive)
{

}

ShellCommandThread::~ShellCommandThread()
{
	if (shellCmdThread_)
	{
        shellCmdThread_->join();
	}
}

void ShellCommandThread::execute()
{
    TRACE_DEBUG("Execute command:" << cmd_);
    excuteState_ = ExcuteState::Command_Start;
	if (shellCmdThread_)
	{
        shellCmdThread_->join();
	}
    // start the thread
    shellCmdThread_ = std::unique_ptr<std::thread>(new std::thread(std::bind(&ShellCommandThread::startThread, this)));
    // start the timer
    resetTimer(5000);
    Core::LoopMain::instance().registerTimer(this);
}

void ShellCommandThread::stop()
{
    TRACE_DEBUG("Stop command:" << cmd_);
    Core::LoopMain::instance().deRegisterTimer(getTimerId());

    Lock lock(mutex_);
    if (excuteState_ == ExcuteState::Command_Start)
    {
        excuteState_ = ExcuteState::Thread_Stop;
    }
    else
    {
        excuteState_ = ExcuteState::InActive;
    }
}

void ShellCommandThread::onTime()
{
    ExcuteState excuteState = ExcuteState::InActive;

    {
        Lock lock(mutex_);
        excuteState = excuteState_;
    }

    TRACE_DEBUG("execute state is " << ExcuteStateToString(excuteState));

    if (excuteState == ExcuteState::Command_Start)
    {
        resetTimer(5000);
        Core::LoopMain::instance().registerTimer(this);
    }
    else if (excuteState == ExcuteState::Command_Stop)
    {
        getCmdOutPutFromFile();
        excuteState_ = ExcuteState::OutPut_Retreived;
        resetTimer();
        Core::LoopMain::instance().registerTimer(this);
    }
    else if (excuteState == ExcuteState::OutPut_Retreived)
    {
        execute();
    }
}

bool ShellCommandThread::isInactive()
{
    return (excuteState_ == ExcuteState::InActive);
}

std::ostream& ShellCommandThread::operator<<(std::ostream& os)
{
    os << "[";
    TimerHandler::ITimer::print(os);
    os << "cmd=" << cmd_
       << ", outPutFile=" << outPutFile_
       << ", cmdOutput=";
    for (auto str : cmdOutput_)
    {
        os << str << std::endl;
    }
    os << "]";
    return os;
}

void ShellCommandThread::startThread()
{
    if (outPutFile_.empty())
    {
        int pid = PlatformWrapper::SystemApi::getPid();
        std::string pidStr = lexical_cast<std::string>(pid);
        RemoveCharacter remover(' ', RemovePlace::LOCATION_FRONT | RemovePlace::LOCATION_MIDDLE | RemovePlace::LOCATION_END);
        std::string filePrefix = remover.removeMultiCh(cmd_, "\t \\/-,|=");
        filePrefix = MagicString + "." + pidStr + "." + filePrefix;
        Random random;
        const std::string& TempPath = Configure::getInstance().getEnvironmentTempPath();
        outPutFile_ = TempPath + "/." + filePrefix + "." + random.generateUpLetterString(10);
	    // delete the previous files
        std::string deletePreviousfiles = std::string("rm ") + TempPath + "/." + filePrefix + std::string("*");
	    system(deletePreviousfiles.c_str());
    }
    const std::string cmd = cmd_ + " > " + outPutFile_;
    system(cmd.c_str());

    // set the thread stopped flag
    {
        Lock lock(mutex_);
        if (excuteState_ == ExcuteState::Command_Start)
        {
            excuteState_ = ExcuteState::Command_Stop;
        }
        else if (excuteState_ == ExcuteState::Thread_Stop)
        {
            excuteState_ = ExcuteState::InActive;
        }
    }
}

void ShellCommandThread::getCmdOutPutFromFile()
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
		if (!oneline.empty())
		{
            lines.push_back(oneline);
		}
    }

    if (!lines.empty())
    {
        cmdOutput_.swap(lines);
    }
}

}
