#include "IpPort.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "Generic.h"
#include "SocketWrapper.h"
#include <string>
namespace Network {

const IpPort IpPort::Null = IpPort();

IpPort::IpPort(const IpPort& ipPort)
:port_(ipPort.port_)
{
}

IpPort::IpPort(unsigned short port)
:port_(port)
{
}

IpPort::IpPort(const std::string& port)
:port_(lexical_cast<unsigned short>(port))
{
}

IpPort& IpPort::operator=(const IpPort& ipPort)
{
    port_ = ipPort.port_;
    return (*this);
}

bool IpPort::operator==(const IpPort& that) const
{
    return port_ == that.port_;
}

bool IpPort::operator!=(const IpPort& that) const
{
    return port_ != that.port_;
}

bool IpPort::operator>(const IpPort& that) const
{
    return port_ > that.port_;
}

bool IpPort::operator<(const IpPort& that) const
{
    return port_ < that.port_;
}

void IpPort::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<unsigned short>(PlatformWrapper::Htons(port_));
}

void IpPort::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read<unsigned short>(port_);
    port_ = PlatformWrapper::Ntohs(port_);
}

std::string IpPort::toString() const
{
    return lexical_cast<std::string>(port_);
}

std::ostream& IpPort::operator<<(std::ostream& os) const
{
    os << toString();
    return os;
}

void IpPort::setPort(unsigned short port)
{
    port_ = port;
}

unsigned short IpPort::getPort() const
{
    return port_;
}

}
