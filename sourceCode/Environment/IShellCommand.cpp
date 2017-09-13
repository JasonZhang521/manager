#include "IShellCommand.h"
namespace Environment {

IShellCommand::IShellCommand()
{

}

IShellCommand::~IShellCommand()
{

}

const CommandOutputString& IShellCommand::getCommandOutput() const
{
    return cmdOutput_;
}

}
