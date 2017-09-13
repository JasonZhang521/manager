#include "Environment.h"
#include <memory>
namespace Environment {
Environment::Environment()
{
}

Environment& Environment::instance()
{
    static std::unique_ptr<Environment> instance(new Environment());
    return *instance;
}

void Environment::registerShellCmd(ShellCommandType cmdType, IShellCommand* cmd)
{
    if (cmd != nullptr)
    {
        cmd->execute();
        cmdDb_[cmdType] = std::move(std::unique_ptr<IShellCommand>(cmd));
    }
}

void Environment::deRegisterShellCmd(ShellCommandType cmdType)
{
    cmdDb_.erase(cmdType);
}

const CommandOutputString& Environment::getShellCmdOutput(ShellCommandType cmdType)
{
    auto it = cmdDb_.find(cmdType);
    if (it != cmdDb_.end())
    {
        std::unique_ptr<IShellCommand>& cmd = it->second;
        if (cmd)
        {
            return cmd->getCommandOutput();
        }
    }

    return InvalidCommandOutputString;
}

}
