#ifndef _NETWORK_IPADDRESS_H_
#define _NETWORK_IPADDRESS_H_
#include <stdint.h>
#include "SocketWrapper.h"
#include "ISerializable.h"

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}
namespace Network {

enum IPFamilyType
{
    IPFamilyV4,
    IPFamilyV6,
    IPFamilyInvalid
};

class IpAddress : public Serialize::ISerializable
{
    IPFamilyType ipType_;
    union
    {
        SocketInetAddress ipv4;
        SocketInet6Address ipv6;
    } addr_;
public:
    IpAddress();
    IpAddress(const IpAddress& ipAddress);
    IpAddress(uint32_t address);
    IpAddress(const uint8_t* ipv6address);
    IpAddress(const SocketInetAddress& address);
    IpAddress(const SocketInet6Address& ipv6address);
    // Can take an IPv4 or IPv6 address in string format.throw an exception if
    // an invalid string (i.e. not a valid IP address format) is given.
    IpAddress(const std::string& address);

    IpAddress& operator=(const IpAddress& ipAddress);

    const SocketInetAddress& getAddressIpv4() const;
    const SocketInet6Address& getAddressIpv6() const;
    void setAddressIpv4(const SocketInetAddress& ipv4Addr);
    void setAddressIpv6(const SocketInet6Address& ipv6Addr);
    IPFamilyType getIPFamilyType() const;

    bool operator==(const IpAddress& other) const;
    bool operator!=(const IpAddress& other) const;
    bool operator>(const IpAddress& rh) const;
    bool operator<(const IpAddress& rh) const;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);
    std::string toString() const;
    std::ostream& operator<<(std::ostream& os) const;

public:
    static const IpAddress Null;
} ;

}

inline std::ostream& operator<<(std::ostream& os, const Network::IpAddress& ipAddress)
{
    return ipAddress.operator <<(os);
}

#endif // _NETWORK_IPADDRESS_H_
