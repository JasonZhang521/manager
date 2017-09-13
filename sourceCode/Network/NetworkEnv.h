#ifndef NETWORKENV_H
#define NETWORKENV_H
#include <vector>
#include <string>
#include "IpAddress.h"

namespace Network {

using IpAddresses = std::vector<IpAddress>;
class NetworkEnv
{
public:
    NetworkEnv();
    static IpAddresses getLocalIpAddress();
    static std::string getHostName();
private:
    static void getIpAddressFromHostName(IpAddresses& addresses);
    static void getIpAddressFromIf(IpAddresses& addresses);
};
}

#endif // NETWORKENV_H
