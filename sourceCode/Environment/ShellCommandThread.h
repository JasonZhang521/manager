#ifndef _ENVIRONMENT_SHELLCOMMANDTHREAD_H_
#define _ENVIRONMENT_SHELLCOMMANDTHREAD_H_
#include "IShellCommand.h"
#include "ITimer.h"
#include "Component.h"
#include "Macro.h"
#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace std {
class thread;
}

namespace Environment {
class ShellCommandThread : public TimerHandler::ITimer, public IShellCommand
{
    enum class ExcuteState
    {
        Command_Start,
        Command_Stop,
        OutPut_Retreived,
        Thread_Stop,
        InActive
    };
    static std::string ExcuteStateToString(ExcuteState state);

    std::string cmd_;
    std::string outPutFile_;
    std::unique_ptr<std::thread> shellCmdThread_;
    ExcuteState excuteState_;
    std::mutex mutex_;
public:
    ShellCommandThread(const std::string& cmd, uint32_t timeout);
    virtual ~ShellCommandThread();
protected:
    virtual void execute();
    virtual void stop();
    virtual void onTime();
    virtual bool isInactive();
    virtual std::ostream& operator<<(std::ostream& os);
private:
    void startThread();
    void getCmdOutPutFromFile();
public:
    GETCLASSNAME(ShellCommandThread)
private:
    static std::string MagicString;
};
}

#endif // _ENVIRONMENT_SHELLCOMMANDTHREAD_H_
