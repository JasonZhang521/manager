#include "NetworkConfig.h"
#include "RemoveCharacter.h"
#include "fstream"

namespace ConfigureManagement {
NetworkConfig::NetworkConfig()
{

}

std::vector<std::string> NetworkConfig::getNodeServerIpPort()
{
    const std::string serverIpPortConfigPath("/opt/HongClusterMgt/config/conf.node.server");
    std::vector<std::string> ipPorts;
    if (!readIpPortFromConfigFile(serverIpPortConfigPath, ipPorts))
    {
        ipPorts.push_back("127.0.0.1:23832");
    }
    return ipPorts;
}

std::vector<std::string> NetworkConfig::getUiServerIpPort()
{
    const std::string serverIpPortConfigPath("/opt/HongClusterMgt/config/conf.ui.server");
    std::vector<std::string> ipPorts;
    if (!readIpPortFromConfigFile(serverIpPortConfigPath, ipPorts))
    {
        ipPorts.push_back("127.0.0.1:23833");
    }
    return ipPorts;
}

bool NetworkConfig::readIpPortFromConfigFile(const std::string& configFile, std::vector<std::string>& ipPorts)
{

    std::ifstream ifs(configFile.c_str());

    if (!ifs.good())
    {
        return false;
    }
    else
    {
        while(ifs.good())
        {
            char buffer[128];
            std::fill(buffer, buffer + 128, 0);
            ifs.getline(buffer, 128);
            std::string str(buffer, 128);
            RemoveCharacter remover;
            str = remover.removeMultiCh(str, " \t");
            ipPorts.push_back(str);
        }
        if (ipPorts.empty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

}
