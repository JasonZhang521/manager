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
    writeBuffer.write(homeDirUsage_);
}

void DiskUsageInfo::unserialize(Serialize::ReadBuffer& readBuffer)
{
    rootDirUsage_.unserialize(readBuffer);
    bootInitDirUsage_.unserialize(readBuffer);
    readBuffer.read(homeDirUsage_);
}

std::ostream& DiskUsageInfo::operator <<(std::ostream& os) const
{
    os << "["
       << "rootDirUsage=" << rootDirUsage_
       << ", bootInitDirUsage=" << bootInitDirUsage_
       << ", homeDirUsage=" << homeDirUsage_
       << "]";
    return os;
}

bool DiskUsageInfo::operator ==(const DiskUsageInfo& info) const
{
    return (rootDirUsage_ == info.rootDirUsage_ &&
            bootInitDirUsage_ == info.bootInitDirUsage_ &&
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

void DiskUsageInfo::update()
{
    updateRootAndBootInitDirUsage();
	updateHomeDirUsage();
}

void DiskUsageInfo::updateRootAndBootInitDirUsage()
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
    }
}

void DiskUsageInfo::updateHomeDirUsage()
{
    using CommandOutputString = std::vector<std::string>;
    const CommandOutputString& strs = Environment::instance().getShellCmdOutput(ShellCommandType::DiskUsageDuHome);
        ShellCommandOutputParse::ParseDuHomeOutput(strs, homeDirUsage_);
}

}
