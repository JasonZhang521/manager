#ifndef _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
#define _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
#include "ShellCommandDataType.h"
#include <string>
#include <vector>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {

using CommandOutputString = std::vector<std::string>;

class ShellCommandGenericOutput
{
    ShellCommandType cmdType_;
    CommandOutputString outputString_;
public:
    ShellCommandGenericOutput();
    ShellCommandGenericOutput(const ShellCommandType& cmdType, const CommandOutputString& output);
    ShellCommandGenericOutput(const ShellCommandGenericOutput& output);
    ShellCommandGenericOutput& operator =(const ShellCommandGenericOutput& output);
    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const ShellCommandGenericOutput& output) const;

    const CommandOutputString& getCommandOutputString() const;
    void setCommandOutputString(const CommandOutputString& outputs);
    const ShellCommandType& getCommand() const;
    void setCommand(const ShellCommandType& cmdType);
};

}

inline std::ostream& operator <<(std::ostream& os, const Environment::ShellCommandGenericOutput& output)
{
    return output.operator <<(os);
}

#endif // _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
