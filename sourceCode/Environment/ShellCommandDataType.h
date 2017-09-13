#ifndef _ENVIRONMENT_SHELLCOMMANDDATATYPE_H_
#define _ENVIRONMENT_SHELLCOMMANDDATATYPE_H_
#include <map>
#include <string>
#include <vector>
#include <ostream>
#include <stdint.h>

namespace Environment {

using CommandOutputString = std::vector<std::string>;

static const CommandOutputString InvalidCommandOutputString;

class ShellCommandString
{
public:
    static const std::string DiskUsageDf;
    static const std::string DiskUsageDuHome;
    static const std::string PsTop10CpuUsage;
    static const std::string PsTop10MemoryUsage;
    static const std::string InvalidCmd;

};

enum class ShellCommandType
{
    DiskUsageDf,
    DiskUsageDuHome,
    PsTop10CpuUsage,
    PsTop10MemoryUsage,
    InvalidType
};

class ShellCommand
{
    static std::map<ShellCommandType, std::string> cmdTypeToCmdString_;
    static std::map<std::string, ShellCommandType> cmdStringToCmdType_;

public:
    static const std::string& getCmdString(ShellCommandType cmdType);
    static ShellCommandType getCmdType(const std::string& cmdStr);
};

}
#endif // SHELLCOMMANDDATATYPE_H
