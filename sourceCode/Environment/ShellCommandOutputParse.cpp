#include "ShellCommandOutputParse.h"
#include "ShellCommandDfOutput.h"
#include "ShellCommandPsTopnCpuUsageOutput.h"
#include "ShellCommandPsTopnMemoryUsageOutput.h"

namespace Environment {

ShellCommandOutputParse::ShellCommandOutputParse()
{

}
/* *** df output
 *
Filesystem        1K-blocks      Used Available Use% Mounted on
/dev/sda2             57591044  20032372  34633156  37% /
tmpfs                  1019896       276   1019620   1% /dev/shm
/dev/sda1               297485     30366    251759  11% /boot
/dev/sr0               3351190   3351190         0 100% /media/RHEL_6.0 x86_64 Disc 1
*/
void ShellCommandOutputParse::ParseDfOutput(const CommandOutputString& strs, ShellCommandDfOutputs& outputs)
{
    outputs.clear();
    for (size_t i = 1; i < strs.size(); ++i)
    {
        ShellCommandDfOutput dfOutput;
        std::string str = strs[i];
        dfOutput.setFileSystem(getFirstDataFromString<std::string>(str));
        dfOutput.setOneKBlock(getFirstDataFromString<uint64_t>(str));
        dfOutput.setUsed(getFirstDataFromString<uint64_t>(str));
        dfOutput.setAvailable(getFirstDataFromString<uint64_t>(str));
        dfOutput.setPecentageUsed(getFirstDataFromString<uint8_t>(str));
        dfOutput.setMountedOn(getFirstDataFromString<std::string>(str));
        outputs.push_back(dfOutput);
    }
}

/* du -s /home
15167896	/home
*/
void ShellCommandOutputParse::ParseDuHomeOutput(const CommandOutputString& strs, uint64_t& used)
{
    if (!strs.empty())
    {
        std::string str = strs[0];
        used = getFirstDataFromString<uint64_t>(str);
    }
}

/* ps -Ao user,uid,comm,pid,pcpu --sort=-pcpu | head -n 10
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
void ShellCommandOutputParse::ParsePsTopnCpuUsageOutput(const CommandOutputString& strs, ShellCommandPsTopnCpuUsageOutputs& outputs)
{
    outputs.clear();
    for (size_t i = 1; i < strs.size(); ++i)
    {
        ShellCommandPsTopnCpuUsageOutput output;
        std::string str = strs[i];
        output.setUser(getFirstDataFromString<std::string>(str));
        output.setUid(getFirstDataFromString<uint16_t>(str));
        output.setCommand(getFirstDataFromString<std::string>(str));
        output.setPid(getFirstDataFromString<uint16_t>(str));
        output.setPercentage(getFirstDataFromString<std::string>(str));
        outputs.push_back(output);
    }
}

void ShellCommandOutputParse::ParsePsTopnMemoryUsageOutput(const CommandOutputString& strs, ShellCommandPsTopnMemoryUsageOutputs& outputs)
{
    outputs.clear();
    for (size_t i = 1; i < strs.size(); ++i)
    {
        ShellCommandPsTopnMemoryUsageOutput output;
        std::string str = strs[i];
        output.setUser(getFirstDataFromString<std::string>(str));
        output.setUid(getFirstDataFromString<uint16_t>(str));
        output.setCommand(getFirstDataFromString<std::string>(str));
        output.setPid(getFirstDataFromString<uint16_t>(str));
        output.setSize(getFirstDataFromString<uint32_t>(str));
        outputs.push_back(output);
    }
}

}
