#include "NetworkEnv.h"
#include "SocketWrapper.h"
namespace Network {
NetworkEnv::NetworkEnv()
{

}

IpAddresses NetworkEnv::getLocalIpAddress()
{
    IpAddresses addresses;

    if (SOCKET_SUCCESS != PlatformWrapper::InitSocket())
    {
        return addresses;
    }

#ifdef WIN32
    getIpAddressFromHostName(addresses);
#else
    getIpAddressFromIf(addresses);
#endif

    return addresses;
}

std::string NetworkEnv::getHostName()
{
    std::string hostname;
    PlatformWrapper::GetHostName(hostname);
    return hostname;
}
void NetworkEnv::getIpAddressFromHostName(IpAddresses& addresses)
{
    std::string hostname;
    if (PlatformWrapper::GetHostName(hostname))
    {
        return;
    }

    SocketHostent* hostent = PlatformWrapper::GetHostByName(hostname);
    if (nullptr == hostent)
    {
        return;
    }

    unsigned int i = 0;
    while (hostent->h_addr_list[i] != nullptr)
    {
        SocketInetAddress *ipAddr = reinterpret_cast<SocketInetAddress *>(hostent->h_addr_list[i]);
        addresses.push_back(IpAddress(*ipAddr));
        i++;
    }
}
void NetworkEnv::getIpAddressFromIf(IpAddresses& addresses)
{
#ifndef WIN32
    SocketIfAddress address = nullptr;
    SocketIfAddress it = nullptr;
    PlatformWrapper::GetIfAddrs(&address);
    it = address;
    while (it != nullptr)
    {
        if (it->ifa_addr->sa_family==AF_INET)
        {
            SocketAddressIn* addressIn = reinterpret_cast<SocketAddressIn*>(it->ifa_addr);
            addresses.push_back(IpAddress(addressIn->sin_addr));
        }
        it = it->ifa_next;
    }
    freeifaddrs(address);
#else
    static_cast<void>(addresses);
#endif
}

}
