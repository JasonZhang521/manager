#ifndef _ENVIRONMENT_SHELLCOMMANDPSTOP10CPUUSAGEOUTPUT_H_
#define _ENVIRONMENT_SHELLCOMMANDPSTOP10CPUUSAGEOUTPUT_H_
#include <string>
#include <ostream>
#include <vector>
#include <stdint.h>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {

/*
 *
USER       UID COMMAND            PID %CPU
jstar      500 ps                4134  5.0
root         0 Xorg              2192  0.3
jstar      500 gnome-terminal    2586  0.1
root         0 init                 1  0.0
root         0 kthreadd             2  0.0
root         0 migration/0          3  0.0
root         0 ksoftirqd/0          4  0.0
root         0 watchdog/0           5  0.0
root         0 migration/1          6  0.0
*/

class ShellCommandPsTopnCpuUsageOutput
{
    std::string user_;
    uint16_t uid_;
    std::string command_;
    uint16_t pid_;
    std::string percentage_;
public:
    ShellCommandPsTopnCpuUsageOutput();
    ShellCommandPsTopnCpuUsageOutput(const ShellCommandPsTopnCpuUsageOutput& output);
    ShellCommandPsTopnCpuUsageOutput& operator=(const ShellCommandPsTopnCpuUsageOutput& output);
    bool operator ==(const ShellCommandPsTopnCpuUsageOutput& output) const;
    std::ostream& operator << (std::ostream& os) const;

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);

    const std::string& getUser() const;
    uint16_t getUid() const;
    const std::string& getCommand() const;
    uint16_t getPid() const;
    const std::string& getPercentage() const;

    void setUser(const std::string& user);
    void setUid(uint16_t uid);
    void setCommand(const std::string& command);
    void setPid(uint16_t pid);
    void setPercentage(const std::string& percentage);
};

using ShellCommandPsTopnCpuUsageOutputs = std::vector<ShellCommandPsTopnCpuUsageOutput>;

}

inline std::ostream& operator << (std::ostream& os, const Environment::ShellCommandPsTopnCpuUsageOutput& output)
{
    return output.operator <<(os);
}

#endif // _ENVIRONMENT_SHELLCOMMANDPSTOP10CPUUSAGEOUTPUT_H
