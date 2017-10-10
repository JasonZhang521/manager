#include "ShellCommandPsTopnCpuUsageOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace Environment {

ShellCommandPsTopnCpuUsageOutput::ShellCommandPsTopnCpuUsageOutput()
{

}

ShellCommandPsTopnCpuUsageOutput::ShellCommandPsTopnCpuUsageOutput(const ShellCommandPsTopnCpuUsageOutput& output)
    : user_(output.user_)
    , uid_(output.uid_)
    , command_(output.command_)
    , pid_(output.pid_)
    , percentage_(output.percentage_)
{

}

ShellCommandPsTopnCpuUsageOutput& ShellCommandPsTopnCpuUsageOutput::operator=(const ShellCommandPsTopnCpuUsageOutput& output)
{
    user_ = output.user_;
    uid_ = output.uid_;
    command_ = output.command_;
    pid_ = output.pid_;
    percentage_ = output.percentage_;
    return (*this);
}

bool ShellCommandPsTopnCpuUsageOutput::operator ==(const ShellCommandPsTopnCpuUsageOutput& output) const
{
    return (user_ == output.user_ &&
            uid_ == output.uid_ &&
            command_ == output.command_ &&
            pid_ == output.pid_ &&
            percentage_ == output.percentage_);
}

std::ostream& ShellCommandPsTopnCpuUsageOutput::operator << (std::ostream& os) const
{
    os << "["
       << "user=" << user_
	   << ", uid=" << uid_
       << ", command=" << command_
       << ", pid=" << pid_
       << ", percentage=" << percentage_
       << "]";
    return os;
}

void ShellCommandPsTopnCpuUsageOutput::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(user_);
    writeBuffer.write(command_);
    writeBuffer.write(pid_);
    writeBuffer.write(percentage_);
}

void ShellCommandPsTopnCpuUsageOutput::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read(user_);
    readBuffer.read(command_);
    readBuffer.read(pid_);
    readBuffer.read(percentage_);
}

const std::string& ShellCommandPsTopnCpuUsageOutput::getUser() const
{
    return user_;
}

uint16_t ShellCommandPsTopnCpuUsageOutput::getUid() const
{
    return uid_;
}
const std::string& ShellCommandPsTopnCpuUsageOutput::getCommand() const
{
    return command_;
}
uint16_t ShellCommandPsTopnCpuUsageOutput::getPid() const
{
    return pid_;
}
const std::string& ShellCommandPsTopnCpuUsageOutput::getPercentage() const
{
    return percentage_;
}

void ShellCommandPsTopnCpuUsageOutput::setUser(const std::string& user)
{
    user_ = user;
}
void ShellCommandPsTopnCpuUsageOutput::setUid(uint16_t uid)
{
    uid_ = uid;
}
void ShellCommandPsTopnCpuUsageOutput::setCommand(const std::string& command)
{
    command_ = command;
}
void ShellCommandPsTopnCpuUsageOutput::setPid(uint16_t pid)
{
    pid_ = pid;
}
void ShellCommandPsTopnCpuUsageOutput::setPercentage(const std::string& percentage)
{
    percentage_ = percentage;
}

}
