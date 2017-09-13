#include "ShellCommandGenericOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace Environment {
ShellCommandGenericOutput::ShellCommandGenericOutput(const std::string& cmd, const CommandOutputString& output)
    : cmd_(cmd)
    , outputString_(output)
{

}

ShellCommandGenericOutput::ShellCommandGenericOutput(const ShellCommandGenericOutput& output)
    : cmd_(output.cmd_)
    , outputString_(output.outputString_)
{

}

ShellCommandGenericOutput& ShellCommandGenericOutput::operator =(const ShellCommandGenericOutput& output)
{
    cmd_ = output.cmd_;
    outputString_ = output.outputString_;
    return *this;
}

void ShellCommandGenericOutput::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(static_cast<uint8_t>(cmd_.size()));
    writeBuffer.write(cmd_.c_str(), cmd_.size());
    writeBuffer.write(static_cast<uint16_t>(outputString_.size()));
    for (auto str : outputString_)
    {
        writeBuffer.write(static_cast<uint16_t>(str.size()));
        writeBuffer.write(str.c_str(), str.size());
    }
}
void ShellCommandGenericOutput::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t size8 = 0;
    char buffer[1024];
    std::fill(buffer, buffer + 1024, 0);
    readBuffer.read(size8);
    readBuffer.read(buffer, size8);
    cmd_ = std::string(buffer, size8);

    uint16_t size16 = 0;
    readBuffer.read(size16);
    CommandOutputString tempStrings;
    for (uint16_t i = 0; i < size16; ++i)
    {
        uint16_t sizeStr = 0;
        readBuffer.read(sizeStr);
        readBuffer.read(buffer, sizeStr);
        tempStrings.push_back(std::string(buffer, sizeStr));
    }
    outputString_.swap(tempStrings);
}

std::ostream& ShellCommandGenericOutput::operator <<(std::ostream& os) const
{
    os << "["
       << "cmd=" << cmd_ << std::endl;
    for (auto str : outputString_)
    {
        os << str << std::endl;
    }
    os << "]";
    return os;
}
bool ShellCommandGenericOutput::operator ==(const ShellCommandGenericOutput& output) const
{
    return (cmd_ == output.cmd_) && (outputString_ == output.outputString_);
}

const CommandOutputString& ShellCommandGenericOutput::getCommandOutputString() const
{
    return outputString_;
}

const std::string& ShellCommandGenericOutput::getCommand() const
{
    return cmd_;
}

}
