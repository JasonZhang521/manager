#ifndef _ENVIRONMENT_SHELLCOMMANDPSTOPNMEMORYUSAGEOUTPUT_H_
#define _ENVIRONMENT_SHELLCOMMANDPSTOPNMEMORYUSAGEOUTPUT_H_
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
USER       UID COMMAND            PID    SZ
root         0 console-kit-dae   2247 4078148
jstar      500 bonobo-activati   2467 555740
jstar      500 nautilus          2464 233684
root         0 rsyslogd          1746 227804
jstar      500 gnome-settings-   2433 163636
jstar      500 clock-applet      2545 153904
jstar      500 pulseaudio        2451 152720
root         0 vmware-vmblock-   1355 152468
jstar      500 gvfs-gdu-volume   2479 152248

*/
class ShellCommandPsTopnMemoryUsageOutput
{
    std::string user_;
    uint16_t uid_;
    std::string command_;
    uint16_t pid_;
    uint32_t size_;
public:
    ShellCommandPsTopnMemoryUsageOutput();
    ShellCommandPsTopnMemoryUsageOutput(const ShellCommandPsTopnMemoryUsageOutput& output);
    ShellCommandPsTopnMemoryUsageOutput& operator=(const ShellCommandPsTopnMemoryUsageOutput& output);
    bool operator ==(const ShellCommandPsTopnMemoryUsageOutput& output) const;
    std::ostream& operator << (std::ostream& os) const;

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);

    const std::string& getUser() const;
    uint16_t getUid() const;
    const std::string& getCommand() const;
    uint16_t getPid() const;
    uint32_t getSize() const;

    void setUser(const std::string& user);
    void setUid(uint16_t uid);
    void setCommand(const std::string& command);
    void setPid(uint16_t pid);
    void setSize(uint32_t size);
};

using ShellCommandPsTopnMemoryUsageOutputs = std::vector<ShellCommandPsTopnMemoryUsageOutput>;

}

inline std::ostream& operator << (std::ostream& os, const Environment::ShellCommandPsTopnMemoryUsageOutput& output)
{
    return output.operator <<(os);
}

#endif // _ENVIRONMENT_SHELLCOMMANDPSTOPNMEMORYUSAGEOUTPUT_H_
