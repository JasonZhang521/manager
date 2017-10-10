#include "ShellCommandGenericOutput.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "Generic.h"

namespace Environment {

ShellCommandGenericOutput::ShellCommandGenericOutput()
    : cmdType_(ShellCommandType::InvalidType)
{

}

ShellCommandGenericOutput::ShellCommandGenericOutput(const ShellCommandType& cmdType, const CommandOutputString& output)
    : cmdType_(cmdType)
    , outputString_(output)
{

}

ShellCommandGenericOutput::ShellCommandGenericOutput(const ShellCommandGenericOutput& output)
    : cmdType_(output.cmdType_)
    , outputString_(output.outputString_)
{

}

ShellCommandGenericOutput& ShellCommandGenericOutput::operator =(const ShellCommandGenericOutput& output)
{
    cmdType_ = output.cmdType_;
    outputString_ = output.outputString_;
    return *this;
}

void ShellCommandGenericOutput::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(static_cast<uint8_t>(toIntegral(cmdType_)));
    writeBuffer.write(static_cast<uint16_t>(outputString_.size()));
    for (auto str : outputString_)
    {
        writeBuffer.write(static_cast<uint16_t>(str.size()));
        writeBuffer.write(str.c_str(), str.size());
    }
}
void ShellCommandGenericOutput::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t type = 0;
    readBuffer.read(type);
    cmdType_ = ShellCommandType(type);

    char buffer[1024];
    std::fill(buffer, buffer + 1024, 0);
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
       << "cmd=" << ShellCommand::getCmdString(cmdType_) << std::endl;
    for (auto str : outputString_)
    {
        os << str << std::endl;
    }
    os << "]";
    return os;
}
bool ShellCommandGenericOutput::operator ==(const ShellCommandGenericOutput& output) const
{
    return (cmdType_ == output.cmdType_) && (outputString_ == output.outputString_);
}

const CommandOutputString& ShellCommandGenericOutput::getCommandOutputString() const
{
    return outputString_;
}

void ShellCommandGenericOutput::setCommandOutputString(const CommandOutputString& outputs)
{
    outputString_ = outputs;
}

const ShellCommandType& ShellCommandGenericOutput::getCommand() const
{
    return cmdType_;
}

void ShellCommandGenericOutput::setCommand(const ShellCommandType& cmdType)
{
    cmdType_ = cmdType;
}

}
