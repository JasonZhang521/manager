#include "ShellCommandOutputParse.h"
#include "RemoveCharacter.h"
#include <sstream>
namespace Environment {

ShellCommandOutputParse::ShellCommandOutputParse()
{

}

void ShellCommandOutputParse::ParseDfOutput(const CommandOutputString& strs, ShellCommandDfOutputs& outPuts)
{
    RemoveCharacter remover;
    for (size_t i = 1; i < strs.size(); ++i)
    {
        ShellCommandDfOutput dfOutput;
        const std::string& online = strs[i];

        // delete the first and last space and tab
        remover.setCharacter(' ');
        std::string str = remover(online);
        remover.setCharacter('\t');
        str = remover(str);

        size_t firstSpace = str.find_first_of(' ');
        size_t firstTab = str.find_first_of('\t');
        size_t pos = firstSpace < firstTab ? firstSpace : firstTab;
        dfOutput.setFileSystem(str.substr(0, pos));

        str = str.substr(pos, str.size() - pos);

        // delete the first and last space and tab
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);
        firstSpace = str.find_first_of(' ');
        firstTab = str.find_first_of('\t');
        pos = firstSpace < firstTab ? firstSpace : firstTab;

		{
            const std::string oneKBlockStr = str.substr(0, pos);
            std::stringstream ss;
            ss << oneKBlockStr;
            uint64_t oneKBlock = 0;
            ss >> oneKBlock;
            dfOutput.setOneKBlock(oneKBlock);
        }


        str = str.substr(pos, str.size() - pos);

        // delete the first and last space and tab
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);

        firstSpace = str.find_first_of(' ');
        firstTab = str.find_first_of('\t');
        pos = firstSpace < firstTab ? firstSpace : firstTab;

		{
            const std::string usedStr = str.substr(0, pos);
            std::stringstream ss;
            ss << usedStr;
            uint64_t used = 0;
            ss >> used;
            dfOutput.setUsed(used);
        }

        str = str.substr(pos, str.size() - pos);

        // delete the first and last space and tab
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);

        firstSpace = str.find_first_of(' ');
        firstTab = str.find_first_of('\t');
        pos = firstSpace < firstTab ? firstSpace : firstTab;

		{
            const std::string availableStr = str.substr(0, pos);
            std::stringstream ss;
            ss << availableStr;
            uint64_t available = 0;
            ss >> available;
            dfOutput.setAvailable(available);
        }
        str = str.substr(pos, str.size() - pos);

        // delete the first and last space and tab
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);

        firstSpace = str.find_first_of(' ');
        firstTab = str.find_first_of('\t');
        pos = firstSpace < firstTab ? firstSpace : firstTab;

		{
            const std::string pecentageUsedStr = str.substr(0, pos - 1);
            std::stringstream ss;
            ss << pecentageUsedStr;
            uint8_t pecentageUsed = 0;
            ss >> pecentageUsed;
            dfOutput.setPecentageUsed(pecentageUsed);
        }

        str = str.substr(pos, str.size() - pos);

        // delete the first and last space and tab
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);

        firstSpace = str.find_first_of(' ');
        firstTab = str.find_first_of('\t');
        pos = firstSpace < firstTab ? firstSpace : firstTab;

        const std::string mountedOn = str.substr(0, pos - 1);
        dfOutput.setMountedOn(mountedOn);

        outPuts.push_back(dfOutput);
    }
}

void ShellCommandOutputParse::ParseDuHomeOutput(const CommandOutputString& strs, uint64_t& used)
{
    RemoveCharacter remover;
    for (size_t i = 0; i < strs.size(); ++i)
    {
        ShellCommandDfOutput dfOutput;
        const std::string& online = strs[i];

        // delete the first and last space and tab
        remover.setCharacter(' ');
        std::string str = remover(online);
        remover.setCharacter('\t');
        str = remover(str);

        size_t firstSpace = str.find_first_of(' ');
        size_t firstTab = str.find_first_of('\t');
        size_t pos = firstSpace < firstTab ? firstSpace : firstTab;

        const std::string UsedStr = str.substr(0, pos - 1);

        std::stringstream ss;
        ss << UsedStr;
        ss >> used;
        break;
    }
}

}
