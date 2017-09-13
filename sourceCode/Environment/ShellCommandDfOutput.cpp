#include "ShellCommandDfOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace Environment {
ShellCommandDfOutput::ShellCommandDfOutput()
{

}

ShellCommandDfOutput::ShellCommandDfOutput(const ShellCommandDfOutput& output)
    : fileSystem_(output.fileSystem_)
    , oneKBlock_(output.oneKBlock_)
    , used_(output.used_)
    , available_(output.available_)
    , pecentageUsed_(output.pecentageUsed_)
    , mountedOn_(output.mountedOn_)
{

}

ShellCommandDfOutput& ShellCommandDfOutput::operator =(const ShellCommandDfOutput& output)
{
    fileSystem_ = output.fileSystem_;
    oneKBlock_ = output.oneKBlock_;
    used_ = output.used_;
    available_ = output.available_;
    pecentageUsed_ = output.pecentageUsed_;
    mountedOn_ = output.mountedOn_;
    return *this;
}

void ShellCommandDfOutput::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(static_cast<uint8_t>(fileSystem_.size()));
    writeBuffer.write(fileSystem_.c_str(), fileSystem_.size());
    writeBuffer.write(oneKBlock_);
    writeBuffer.write(used_);
    writeBuffer.write(available_);
    writeBuffer.write(pecentageUsed_);
    writeBuffer.write(static_cast<uint8_t>(mountedOn_.size()));
    writeBuffer.write(mountedOn_.c_str(), mountedOn_.size());
}

void ShellCommandDfOutput::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t size = 0;
    readBuffer.read(size);
    char buffer[256];
    readBuffer.read(buffer, size);
    fileSystem_ = std::string(buffer, size);
    readBuffer.read(oneKBlock_);
    readBuffer.read(used_);
    readBuffer.read(available_);
    readBuffer.read(pecentageUsed_);
    readBuffer.read(size);
    readBuffer.read(buffer, size);
    mountedOn_ = std::string(buffer, size);
}

std::ostream& ShellCommandDfOutput::operator <<(std::ostream& os) const
{
    os << "["
       << "fileSystem=" << fileSystem_
       << ", oneKBlock=" << oneKBlock_
       << ", used=" << used_
       << ", available=" << available_
       << ", pecentageUsed=" << static_cast<int>(pecentageUsed_)
       << ", mountedOn=" << mountedOn_
       << "]";
    return os;
}

bool ShellCommandDfOutput::operator ==(const ShellCommandDfOutput& output) const
{
    return (fileSystem_ == output.fileSystem_ &&
            oneKBlock_ == output.oneKBlock_ &&
            used_ == output.used_ &&
            available_ == output.available_ &&
            pecentageUsed_ == output.pecentageUsed_ &&
            mountedOn_ == output.mountedOn_);
}


}
