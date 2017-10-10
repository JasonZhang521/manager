#include "ShellCommandPsTopnMemoryUsageOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace Environment {

ShellCommandPsTopnMemoryUsageOutput::ShellCommandPsTopnMemoryUsageOutput()
{

}

ShellCommandPsTopnMemoryUsageOutput::ShellCommandPsTopnMemoryUsageOutput(const ShellCommandPsTopnMemoryUsageOutput& output)
    : user_(output.user_)
    , uid_(output.uid_)
    , command_(output.command_)
    , pid_(output.pid_)
    , size_(output.size_)
{

}

ShellCommandPsTopnMemoryUsageOutput& ShellCommandPsTopnMemoryUsageOutput::operator=(const ShellCommandPsTopnMemoryUsageOutput& output)
{
    user_ = output.user_;
    uid_ = output.uid_;
    command_ = output.command_;
    pid_ = output.pid_;
    size_ = output.size_;
    return (*this);
}

bool ShellCommandPsTopnMemoryUsageOutput::operator ==(const ShellCommandPsTopnMemoryUsageOutput& output) const
{
    return (user_ == output.user_ &&
            uid_ == output.uid_ &&
            command_ == output.command_ &&
            pid_ == output.pid_ &&
            size_ == output.size_);
}

std::ostream& ShellCommandPsTopnMemoryUsageOutput::operator << (std::ostream& os) const
{
    os << "["
       << "user=" << user_
	   << ", uid=" << uid_
       << ", command=" << command_
       << ", pid=" << pid_
       << ", size=" << size_
       << "]";
    return os;
}

void ShellCommandPsTopnMemoryUsageOutput::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(user_);
    writeBuffer.write(command_);
    writeBuffer.write(pid_);
    writeBuffer.write(size_);
}

void ShellCommandPsTopnMemoryUsageOutput::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read(user_);
    readBuffer.read(command_);
    readBuffer.read(pid_);
    readBuffer.read(size_);
}

const std::string& ShellCommandPsTopnMemoryUsageOutput::getUser() const
{
    return user_;
}

uint16_t ShellCommandPsTopnMemoryUsageOutput::getUid() const
{
    return uid_;
}

const std::string& ShellCommandPsTopnMemoryUsageOutput::getCommand() const
{
    return command_;
}

uint16_t ShellCommandPsTopnMemoryUsageOutput::getPid() const
{
    return pid_;
}

uint32_t ShellCommandPsTopnMemoryUsageOutput::getSize() const
{
    return size_;
}

void ShellCommandPsTopnMemoryUsageOutput::setUser(const std::string& user)
{
    user_ = user;
}

void ShellCommandPsTopnMemoryUsageOutput::setUid(uint16_t uid)
{
    uid_ = uid;
}

void ShellCommandPsTopnMemoryUsageOutput::setCommand(const std::string& command)
{
    command_ = command;
}

void ShellCommandPsTopnMemoryUsageOutput::setPid(uint16_t pid)
{
    pid_ = pid;
}

void ShellCommandPsTopnMemoryUsageOutput::setSize(uint32_t size)
{
    size_ = size;
}

}
