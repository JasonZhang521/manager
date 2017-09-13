#include "IpAddress.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include <string.h>
#include <sstream>
#include <stdexcept>

namespace Network {

const IpAddress IpAddress::Null = IpAddress();

IpAddress::IpAddress()
:ipType_(IPFamilyInvalid)
{
    ::memset(&addr_.ipv4, 0, sizeof(SocketInetAddress));
    ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));
}

IpAddress::IpAddress(const IpAddress& ipAddress)
:ipType_(ipAddress.ipType_)
{
   if (ipType_ == IPFamilyV4)
   {
       ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));
       ::memcpy(&addr_.ipv4, &ipAddress.addr_.ipv4, sizeof(SocketInetAddress));
   }
   else if (ipType_ == IPFamilyV6)
   {
       ::memset(&addr_.ipv4, 0, sizeof(SocketInet6Address));
       ::memcpy(&addr_.ipv6, &ipAddress.addr_.ipv6, sizeof(SocketInet6Address));
   }
}

IpAddress::IpAddress(uint32_t address)
:ipType_(IPFamilyV4)
{
    ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));
    uint32_t addr = htonl(address);
    ::memcpy(&addr_.ipv4, &addr, sizeof(SocketInetAddress));
}

IpAddress::IpAddress(const uint8_t* ipv6address)
:ipType_(IPFamilyV6)
{
    ::memset(&addr_.ipv4, 0, sizeof(SocketInetAddress));
    ::memcpy(&addr_.ipv6, ipv6address, sizeof(SocketInet6Address));
}

IpAddress::IpAddress(const SocketInetAddress& address)
:ipType_(IPFamilyV4)
{
    ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));
    ::memcpy(&addr_.ipv4, &address, sizeof(SocketInetAddress));
}

IpAddress::IpAddress(const SocketInet6Address& ipv6address)
:ipType_(IPFamilyV6)
{
    ::memset(&addr_.ipv4, 0, sizeof(SocketInetAddress));
    ::memcpy(&addr_.ipv6, &ipv6address, sizeof(SocketInet6Address));
}

IpAddress::IpAddress(const std::string& address)
{
    ::memset(&addr_.ipv4, 0, sizeof(SocketInetAddress));
    ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));

    if (PlatformWrapper::InetPton(SOCKET_AF_INET, address.c_str(), &addr_.ipv4.s_addr))
    {
        ipType_ = IPFamilyV4;
    }
    else if(PlatformWrapper::InetPton(SOCKET_AF_INET, address.c_str(), &addr_.ipv6.s6_addr))
    {
        ipType_ = IPFamilyV6;
    }
    else
    {
        ipType_ = IPFamilyInvalid;
        throw std::invalid_argument(std::string("Invalid ip address: ") + address);
    }
}

IpAddress& IpAddress::operator=(const IpAddress& ipAddress)
{
    ipType_ = ipAddress.ipType_;
    if (ipType_ == IPFamilyV4)
    {
        ::memset(&addr_.ipv6, 0, sizeof(SocketInet6Address));
        ::memcpy(&addr_.ipv4, &ipAddress.addr_.ipv4, sizeof(SocketInetAddress));
    }
    else if (ipType_ == IPFamilyV6)
    {
        ::memset(&addr_.ipv4, 0, sizeof(SocketInet6Address));
        ::memcpy(&addr_.ipv6, &ipAddress.addr_.ipv6, sizeof(SocketInet6Address));
    }
    return *this;
}

const SocketInetAddress& IpAddress::getAddressIpv4() const
{
    return addr_.ipv4;
}

const SocketInet6Address& IpAddress::getAddressIpv6() const
{
    return addr_.ipv6;
}

void IpAddress::setAddressIpv4(const SocketInetAddress& ipv4Addr)
{
    addr_.ipv4 = ipv4Addr;
    ipType_ = IPFamilyV4;
}

void IpAddress::setAddressIpv6(const SocketInet6Address& ipv6Addr)
{
    addr_.ipv6 = ipv6Addr;
    ipType_ = IPFamilyV6;
}

IPFamilyType IpAddress::getIPFamilyType() const
{
    return ipType_;
}

bool IpAddress::operator==(const IpAddress& other) const
{
    if (ipType_ == IPFamilyV4 && other.ipType_ == IPFamilyV4)
    {
        return (::memcmp(&addr_.ipv4, &other.addr_.ipv4, sizeof(SocketInetAddress)) == 0);
    }

    if (ipType_ == IPFamilyV6 && other.ipType_ == IPFamilyV6)
    {
        return (::memcmp(&addr_.ipv6, &other.addr_.ipv6, sizeof(SocketInet6Address)) == 0);
    }

    if (ipType_ == IPFamilyInvalid && ipType_ == IPFamilyInvalid)
    {
        return true;
    }

    return false;
}

bool IpAddress::operator!=(const IpAddress& other) const
{
    return !(*this == other);
}

bool IpAddress::operator>(const IpAddress& rh) const
{
    if (ipType_ == rh.ipType_)
    {
        switch (ipType_)
        {
            case IPFamilyV4:
                return ::memcmp(&addr_.ipv4, &rh.addr_.ipv4, 4) > 0;

            case IPFamilyV6:
                // Not supported... yet
                return ::memcmp(&addr_.ipv6, &rh.addr_.ipv6, 16) > 0;
            default:
                return false;
        }
    }

    // If the addresses are of different type, they are still comparable.
    if (ipType_ > rh.ipType_)
    {
        return true;
    }

    return false;
}

bool IpAddress::operator<(const IpAddress& rh) const
{
    return !(*this > rh) && (*this != rh);
}

void IpAddress::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(ipType_);
    if (ipType_ == IPFamilyV4)
    {
        writeBuffer.write(&addr_.ipv4, sizeof(SocketInetAddress));
    }
    else if (ipType_ == IPFamilyV6)
    {
        writeBuffer.write(&addr_.ipv6, sizeof(SocketInet6Address));
    }
}

void IpAddress::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t ipType = 0;
    readBuffer.read<uint8_t>(ipType);
    ipType_ = static_cast<IPFamilyType>(ipType);
    if (ipType_ == IPFamilyV4)
    {
        readBuffer.read(&addr_.ipv4, sizeof(SocketInetAddress));
    }
    else if (ipType_ == IPFamilyV6)
    {
        readBuffer.read(&addr_.ipv6, sizeof(SocketInet6Address));
    }
}

std::string IpAddress::toString() const
{
    std::ostringstream os;
    char               addr4buf[16]; // big enough for IPv4
    char               addr6buf[46]; // big enough for IPv6
    std::fill(addr4buf, addr4buf + sizeof(addr4buf), 0);
    std::fill(addr6buf, addr6buf + sizeof(addr6buf), 0);

    switch (ipType_)
    {
        case IPFamilyV4:
            if (PlatformWrapper::InetNtop(AF_INET, &addr_.ipv4, addr4buf, sizeof(addr4buf)) == 0)
            {
                os << "Illegal_v4_IpAddress";
            }
            os << addr4buf;
            break;

        case IPFamilyV6:
            if (PlatformWrapper::InetNtop(AF_INET6, &addr_.ipv6, addr6buf, sizeof(addr6buf)) == 0)
            {
                os << "Illegal_v6_IpAddress";
            }
            os << addr6buf;
            break;

        default:
            os << "Invalid_IpAddress";
            break;
    }

    return os.str();
}

std::ostream& IpAddress::operator<<(std::ostream& os) const
{
    os << toString();
    return os;
}


}
