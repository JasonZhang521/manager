#ifndef _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
#define _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
#include "ShellCommandDataType.h"
#include "ShellCommandDfOutput.h"

namespace Environment {
class ShellCommandOutputParse
{
public:
    ShellCommandOutputParse();
    static void ParseDfOutput(const CommandOutputString& strs, ShellCommandDfOutputs& outPuts);
    static void ParseDuHomeOutput(const CommandOutputString& strs, uint64_t& used);
};

}

#endif // _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
