#include "ShellCommandDataType.h"
namespace Environment {

const std::string ShellCommandString::DiskUsageDf("df");
const std::string ShellCommandString::DiskUsageDuHome("du -s /home");
const std::string ShellCommandString::PsTop10CpuUsage("ps -Ao user,uid,comm,pid,pcpu --sort=-pcpu | head -n 10");
const std::string ShellCommandString::PsTop10MemoryUsage("ps -Ao user,uid,comm,pid,size --sort=-size | head -n 10");
const std::string ShellCommandString::InvalidCmd("InvalidCmd");

std::map<ShellCommandType, std::string> ShellCommand::cmdTypeToCmdString_ =
{
    {ShellCommandType::DiskUsageDf,        ShellCommandString::DiskUsageDf},
    {ShellCommandType::DiskUsageDuHome,    ShellCommandString::DiskUsageDuHome},
    {ShellCommandType::PsTop10CpuUsage,    ShellCommandString::PsTop10CpuUsage},
    {ShellCommandType::PsTop10MemoryUsage, ShellCommandString::PsTop10MemoryUsage}
};

std::map<std::string, ShellCommandType> ShellCommand::cmdStringToCmdType_ =
{
    {ShellCommandString::DiskUsageDf,        ShellCommandType::DiskUsageDf},
    {ShellCommandString::DiskUsageDuHome,    ShellCommandType::DiskUsageDuHome},
    {ShellCommandString::PsTop10CpuUsage,    ShellCommandType::PsTop10CpuUsage},
    {ShellCommandString::PsTop10MemoryUsage, ShellCommandType::PsTop10MemoryUsage}
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
