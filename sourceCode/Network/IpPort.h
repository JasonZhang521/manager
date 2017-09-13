#ifndef _NETWORK_IPPORT_H_
#define _NETWORK_IPPORT_H_
#include "ISerializable.h"
#include <string>
namespace Network {

class IpPort : public Serialize::ISerializable
{
    // port number in network byte order
    unsigned short port_;
public:
    IpPort(const IpPort& ipPort);
    IpPort(unsigned short port = 0);
    IpPort(const std::string& port);
    IpPort& operator=(const IpPort& ipPort);
    bool operator==(const IpPort& that) const;
    bool operator!=(const IpPort& that) const;
    bool operator>(const IpPort& that) const;
    bool operator<(const IpPort& that) const;

    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer);
    std::string toString() const;
    std::ostream& operator<<(std::ostream& os) const;

    void setPort(unsigned short port);
    unsigned short getPort() const;
public:
    static const IpPort Null;
};

}
#endif // _NETWORK_IPPORT_H_
