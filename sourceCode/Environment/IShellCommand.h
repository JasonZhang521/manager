#ifndef _ENVIRONMENT_ISHELLCOMMAND_H_
#define _ENVIRONMENT_ISHELLCOMMAND_H_
#include "ShellCommandDataType.h"
#include <vector>
#include <string>

namespace Environment {

class IShellCommand
{
protected:
    CommandOutputString cmdOutput_;
public:
    IShellCommand();
    virtual ~IShellCommand();
    virtual void execute() = 0;
    virtual void stop() = 0;
    virtual bool isInactive() = 0;
    virtual const CommandOutputString& getCommandOutput() const;
};
}

#endif // _ENVIRONMENT_ISHELLCOMMAND_H_
