#include "DiskUsageInfo.h"
#include "ShellCommandDataType.h"
#include "ShellCommandOutputParse.h"
#include "Environment.h"
#include "ShellCommandDfOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include <ostream>
namespace Environment {
DiskUsageInfo::DiskUsageInfo()
{

}

void DiskUsageInfo::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    rootDirUsage_.serialize(writeBuffer);
    bootInitDirUsage_.serialize(writeBuffer);
    dfHomeDirUsage_.serialize(writeBuffer);
    writeBuffer.write(homeDirUsage_);
}

void DiskUsageInfo::unserialize(Serialize::ReadBuffer& readBuffer)
{
    rootDirUsage_.unserialize(readBuffer);
    bootInitDirUsage_.unserialize(readBuffer);
    dfHomeDirUsage_.unserialize(readBuffer);
    readBuffer.read(homeDirUsage_);
}

std::ostream& DiskUsageInfo::operator <<(std::ostream& os) const
{
    os << "["
       << "rootDirUsage=" << rootDirUsage_
       << ", bootInitDirUsage=" << bootInitDirUsage_
       << ", dfHomeDirUsage=" << dfHomeDirUsage_
       << ", homeDirUsage=" << homeDirUsage_
       << "]";
    return os;
}

bool DiskUsageInfo::operator ==(const DiskUsageInfo& info) const
{
    return (rootDirUsage_ == info.rootDirUsage_ &&
            bootInitDirUsage_ == info.bootInitDirUsage_ &&
            dfHomeDirUsage_ == info.dfHomeDirUsage_ &&
            homeDirUsage_ == info.homeDirUsage_);
}

const ShellCommandDfOutput& DiskUsageInfo::getRootDirUsage() const
{
	return rootDirUsage_;
}

void DiskUsageInfo::setRootDirUsage(const ShellCommandDfOutput& output)
{
	rootDirUsage_ = output;
}

const ShellCommandDfOutput& DiskUsageInfo::getBootInitDirUsage() const
{
	return bootInitDirUsage_;
}

void DiskUsageInfo::setBootInitDirUsage(const ShellCommandDfOutput& output)
{
	bootInitDirUsage_ = output;
}

const ShellCommandDfOutput& DiskUsageInfo::getDfHomeDirUsage() const
{
    return dfHomeDirUsage_;
}

void DiskUsageInfo::setDfHomeDirUsage(const ShellCommandDfOutput& output)
{
    dfHomeDirUsage_ = output;
}

uint64_t DiskUsageInfo::getHomeDirUsage() const
{
    return homeDirUsage_;
}

void DiskUsageInfo::setHomeDirUsage(uint64_t usage)
{
    homeDirUsage_ = usage;
}

void DiskUsageInfo::update()
{
    updateDfCommandDirUsage();
	updateHomeDirUsage();
}

void DiskUsageInfo::updateDfCommandDirUsage()
{
    using CommandOutputString = std::vector<std::string>;
    const CommandOutputString& strs = Environment::instance().getShellCmdOutput(ShellCommandType::DiskUsageDf);
    ShellCommandDfOutputs dfOutputs;
    ShellCommandOutputParse::ParseDfOutput(strs, dfOutputs);
    for (auto dfOutput : dfOutputs)
    {
        if (dfOutput.getMountedOn() == std::string("/"))
        {
            rootDirUsage_ = dfOutput;
        }

        if (dfOutput.getMountedOn() == std::string("/boot"))
        {
            bootInitDirUsage_ = dfOutput;
        }

        if (dfOutput.getMountedOn() == std::string("/home"))
        {
            dfHomeDirUsage_ = dfOutput;
        }
    }
}

void DiskUsageInfo::updateHomeDirUsage()
{
    using CommandOutputString = std::vector<std::string>;
    const CommandOutputString& strs = Environment::instance().getShellCmdOutput(ShellCommandType::DiskUsageDuHome);
        ShellCommandOutputParse::ParseDuHomeOutput(strs, homeDirUsage_);
}

}
