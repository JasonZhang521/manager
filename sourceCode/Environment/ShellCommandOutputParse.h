#ifndef _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
#define _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
#include "RemoveCharacter.h"
#include "Generic.h"
#include <string>
#include <vector>

namespace Environment {

class ShellCommandDfOutput;
class ShellCommandPsTopnCpuUsageOutput;
class ShellCommandPsTopnMemoryUsageOutput;

using CommandOutputString = std::vector<std::string>;
using ShellCommandDfOutputs = std::vector<ShellCommandDfOutput>;
using ShellCommandPsTopnCpuUsageOutputs = std::vector<ShellCommandPsTopnCpuUsageOutput>;
using ShellCommandPsTopnMemoryUsageOutputs = std::vector<ShellCommandPsTopnMemoryUsageOutput>;

class ShellCommandOutputParse
{
public:
    ShellCommandOutputParse();
    static void ParseDfOutput(const CommandOutputString& strs, ShellCommandDfOutputs& outputs);
    static void ParseDuHomeOutput(const CommandOutputString& strs, uint64_t& used);
    static void ParsePsTopnCpuUsageOutput(const CommandOutputString& strs, ShellCommandPsTopnCpuUsageOutputs& outputs);
    static void ParsePsTopnMemoryUsageOutput(const CommandOutputString& strs, ShellCommandPsTopnMemoryUsageOutputs& outputs);

    template<typename T>
    static T getFirstDataFromString(std::string& str)
    {
        if (str.empty())
        {
            return T();
        }

        RemoveCharacter remover;
        str = remover.removeMultiCh(str, " \t");

        size_t firstSpace = str.find_first_of(' ');
        size_t firstTab = str.find_first_of('\t');
        size_t pos = firstSpace < firstTab ? firstSpace : firstTab;

        std::string DataStr;
        if (pos != std::string::npos)
        {
            DataStr = str.substr(0, pos);
            str = str.substr(pos, str.size() - pos);
        }
        else
        {
            DataStr = str;
            str.clear();
        }

        T data = lexical_cast<T>(DataStr);
        return data;
    }
};

}

#endif // _ENVIRONMENT_SHELLCOMMANDOUTPUTPARSE_H_
