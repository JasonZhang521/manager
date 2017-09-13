#include "IpSocketEndpoint.h"
#include "string.h"
#include <stdexcept>
namespace Network {

const IpSocketEndpoint IpSocketEndpoint::Null;
const IpSocketEndpoint IpSocketEndpoint::BroadCastAddress("0.0.0.0:0");

IpSocketEndpoint::IpSocketEndpoint()
{
}

IpSocketEndpoint::IpSocketEndpoint(const IpSocketEndpoint& ipSocketEndPoint)
    :ipAddress_(ipSocketEndPoint.ipAddress_)
    ,ipPort_(ipSocketEndPoint.ipPort_)
{
}

IpSocketEndpoint::IpSocketEndpoint(const IpAddress& ipAddress, const IpPort& ipPort)
    :ipAddress_(ipAddress)
    ,ipPort_(ipPort)
{
}

IpSocketEndpoint::IpSocketEndpoint(const std::string& ipAndPort)
{
    parse(ipAndPort);
}

IpSocketEndpoint::IpSocketEndpoint(const SocketAddress& socketAddress)
{
    if (socketAddress.sa_family == SOCKET_AF_INET)
    {
        const SocketAddressIn* addr = reinterpret_cast<const SocketAddressIn*>(&socketAddress);
        ipAddress_.setAddressIpv4(addr->sin_addr);
        ipPort_.setPort(addr->sin_port);
    }
    else if (socketAddress.sa_family == SOCKET_AF_INET6)
    {
        const SocketAddressIn6* addr = reinterpret_cast<const SocketAddressIn6*>(&socketAddress);
        ipAddress_.setAddressIpv6(addr->sin6_addr);
        ipPort_.setPort(addr->sin6_family);
    }
    else
    {
        throw std::invalid_argument("Invalid format of ip socket address family");
    }
}

void IpSocketEndpoint::parse(const std::string& ipAndPort)
{
    // We make a tokenizer to verify that the address to be parsed is a ipv4
    // else we asume v6.
    std::string ipAddressString(ipAndPort.c_str());     // Must save . token will put in nullptr char
    const char* tokenizer = ipAddressString.c_str();
    const char* result    = strtok(const_cast<char*>(tokenizer), ".");
    int         count     = 0;
    while (result != nullptr)
    {
        result = strtok(nullptr, ".");
        ++count;
    }

    if (count == 4)
    {
        parseIpAndPortV4(ipAndPort);
    }
    else
    {
        throw std::invalid_argument("Invalid format of ip socket endpoint");
    }
}

void IpSocketEndpoint::parseIpAndPortV4(const std::string& ipAndPort)
{
    size_t pos = ipAndPort.find(":");
    if (pos == std::string::npos || ipAndPort.length() <= (pos + 1))
    {
        throw std::invalid_argument("Invalid format of ip socket endpoint");
    }

    std::string ipAddress = ipAndPort.substr(0, pos);
    std::string ipPort    = ipAndPort.substr(pos + 1);
    ipAddress_ = ipAddress;
    ipPort_ = ipPort;
}

IpSocketEndpoint& IpSocketEndpoint::operator=(const IpSocketEndpoint& ipSocketEndpoint)
{
    ipAddress_ = ipSocketEndpoint.ipAddress_;
    ipPort_ = ipSocketEndpoint.ipPort_;
    return (*this);
}

bool IpSocketEndpoint::operator==(const IpSocketEndpoint& ipSocketEndpoint) const
{
    return (ipAddress_ == ipSocketEndpoint.ipAddress_ && ipPort_ == ipSocketEndpoint.ipPort_);
}

bool IpSocketEndpoint::operator!=(const IpSocketEndpoint& ipSocketEndpoint) const
{
    return !operator==(ipSocketEndpoint);
}

bool IpSocketEndpoint::operator>(const IpSocketEndpoint& ipSocketEndpoint) const
{
    return (ipAddress_ > ipSocketEndpoint.ipAddress_ ||
           (ipAddress_ == ipSocketEndpoint.ipAddress_ && ipPort_ > ipSocketEndpoint.ipPort_));
}

bool IpSocketEndpoint::operator<(const IpSocketEndpoint& ipSocketEndpoint) const
{
    return (ipAddress_ < ipSocketEndpoint.ipAddress_ ||
           (ipAddress_ == ipSocketEndpoint.ipAddress_ && ipPort_ < ipSocketEndpoint.ipPort_));
}

void IpSocketEndpoint::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    ipAddress_.serialize(writeBuffer);
    ipPort_.serialize(writeBuffer);
}

void IpSocketEndpoint::unserialize(Serialize::ReadBuffer& readBuffer)
{
    ipAddress_.unserialize(readBuffer);
    ipPort_.unserialize(readBuffer);
}

std::string IpSocketEndpoint::toString() const
{
    return ipAddress_.toString() + ":" + ipPort_.toString();
}

IPFamilyType IpSocketEndpoint::getIpFamilyType() const
{
    return ipAddress_.getIPFamilyType();
}

SocketAddressFamily IpSocketEndpoint::getSocketAddressFamily() const
{
    if (IPFamilyV4 == ipAddress_.getIPFamilyType())
    {
        return SOCKET_AF_INET;
    }
    else if (IPFamilyV6 == ipAddress_.getIPFamilyType())
    {
        return SOCKET_AF_INET6;
    }
    else
    {
        return SOCKET_AF_UNSPEC;
    }
}

IpAddress IpSocketEndpoint::getIpAddress() const
{
    return ipAddress_;
}

IpPort IpSocketEndpoint::getIpPort() const
{
    return ipPort_;
}

void IpSocketEndpoint::setIpAddress(const IpAddress& address)
{
    ipAddress_ = address;
}

void IpSocketEndpoint::setIpPort(const IpPort& port)
{
    ipPort_ = port;
}

SocketAddressIn IpSocketEndpoint::getSocketAddressIpv4() const
{
    SocketAddressIn address;
    memset(&address, 0, sizeof(SocketAddressIn));
    address.sin_family = SOCKET_AF_INET;
    address.sin_port = ipPort_.getPort();
    address.sin_addr = ipAddress_.getAddressIpv4();
    return address;
}

SocketAddressIn6 IpSocketEndpoint::getSocketAddressIpv6() const
{
    SocketAddressIn6 address;
    memset(&address, 0, sizeof(SocketAddressIn6));
    address.sin6_family = SOCKET_AF_INET6;
    address.sin6_port = ipPort_.getPort();
    address.sin6_addr = ipAddress_.getAddressIpv6();
    return address;
}

std::ostream& IpSocketEndpoint::operator<<(std::ostream& os) const
{
    os << toString();
    return os;
}

bool IpSocketEndpoint::isValid() const
{
    return (operator !=(Null));
}

} // out of namespace
