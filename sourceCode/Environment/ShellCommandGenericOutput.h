#ifndef _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
#define _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
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
    std::string cmd_;
    CommandOutputString outputString_;
public:
    ShellCommandGenericOutput(const std::string& cmd, const CommandOutputString& output);
    ShellCommandGenericOutput(const ShellCommandGenericOutput& output);
    ShellCommandGenericOutput& operator =(const ShellCommandGenericOutput& output);
    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const ShellCommandGenericOutput& output) const;

    const CommandOutputString& getCommandOutputString() const;
    const std::string& getCommand() const;
};
}
#endif // _ENVIRONMENT_SHELLCOMMANDGENERICOUTPUT_H_
