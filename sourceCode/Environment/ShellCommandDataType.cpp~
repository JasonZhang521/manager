#include "ShellCommandDataType.h"
namespace Environment {

const std::string ShellCommandString::DiskUsageDf("df");
const std::string ShellCommandString::DiskUsageDuHome("du -s /home");
const std::string ShellCommandString::PsTop10CpuUsage("ps -Ao user,uid,comm,pid,pcpu --sort=-pcpu | head -n 10");
const std::string ShellCommandString::PsTop10MemoryUsage("ps -Ao user,uid,comm,pid,size --sort=-size | head -n 10");
const std::string ShellCommandString::NvidiaSmiGpu("nvidia-smi -q");
const std::string ShellCommandString::InfiniBandStat("ibstat");
const std::string ShellCommandString::Shutdown("shutdown");
const std::string ShellCommandString::Reboot("shutdown -r");
const std::string ShellCommandString::InvalidCmd("InvalidCmd");

std::map<ShellCommandType, std::string> ShellCommand::cmdTypeToCmdString_ =
{
    {ShellCommandType::DiskUsageDf,        ShellCommandString::DiskUsageDf},
    {ShellCommandType::DiskUsageDuHome,    ShellCommandString::DiskUsageDuHome},
    {ShellCommandType::PsTop10CpuUsage,    ShellCommandString::PsTop10CpuUsage},
    {ShellCommandType::PsTop10MemoryUsage, ShellCommandString::PsTop10MemoryUsage},
    {ShellCommandType::NvidiaSmiGpu,       ShellCommandString::NvidiaSmiGpu},
    {ShellCommandType::InfiniBandStat,     ShellCommandString::InfiniBandStat},
    {ShellCommandType::Shutdown,           ShellCommandString::Shutdown},
    {ShellCommandType::Reboot,             ShellCommandString::Reboot}
};

std::map<std::string, ShellCommandType> ShellCommand::cmdStringToCmdType_ =
{
    {ShellCommandString::DiskUsageDf,        ShellCommandType::DiskUsageDf},
    {ShellCommandString::DiskUsageDuHome,    ShellCommandType::DiskUsageDuHome},
    {ShellCommandString::PsTop10CpuUsage,    ShellCommandType::PsTop10CpuUsage},
    {ShellCommandString::PsTop10MemoryUsage, ShellCommandType::PsTop10MemoryUsage},
    {ShellCommandString::NvidiaSmiGpu,       ShellCommandType::NvidiaSmiGpu},
    {ShellCommandString::InfiniBandStat,     ShellCommandType::InfiniBandStat},
    {ShellCommandString::Shutdown,           ShellCommandType::Shutdown},
    {ShellCommandString::Reboot,             ShellCommandType::Reboot}
};



const std::string& ShellCommand::getCmdString(ShellCommandType cmdType)
{
    auto it = cmdTypeToCmdString_.find(cmdType);
    if (it == cmdTypeToCmdString_.end())
    {
        return ShellCommandString::InvalidCmd;
    }
    else
    {
        return it->second;
    }
}

ShellCommandType ShellCommand::getCmdType(const std::string& cmdStr)
{
    auto it = cmdStringToCmdType_.find(cmdStr);
    if (it == cmdStringToCmdType_.end())
    {
        return ShellCommandType::InvalidType;
    }
    else
    {
        return it->second;
    }
}
}
