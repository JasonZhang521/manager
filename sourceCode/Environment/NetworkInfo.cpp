#include "NetworkInfo.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "Trace.h"
#include "fstream"

namespace Environment {
NetworkInfo::NetworkInfo()
{

}

NetworkInfo::NetworkInfo(const NetworkInfo& info)
    :macAddress_(info.macAddress_)
    ,hostIpAddresses_(info.hostIpAddresses_)
{

}

NetworkInfo& NetworkInfo::operator =(const NetworkInfo& info)
{
    macAddress_ = info.macAddress_;
    hostIpAddresses_ = info.hostIpAddresses_;
    return *this;
}

void NetworkInfo::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(static_cast<uint8_t>(macAddress_.size()));
    writeBuffer.write(macAddress_.c_str(), macAddress_.size());
    writeBuffer.write(static_cast<uint8_t>(hostIpAddresses_.size()));
    for (auto ip : hostIpAddresses_)
    {
        ip.serialize(writeBuffer);
    }
}

void NetworkInfo::unserialize(Serialize::ReadBuffer& readBuffer)
{
    char buffer[128];
    std::fill(buffer, buffer + 128, 0);
    uint8_t size = 0;

    // mac address
    readBuffer.read(size);
    readBuffer.read(buffer, size);
    macAddress_ = std::string(buffer, size);

    // host ip address
    readBuffer.read(size);
    for (int i = 0; i < size; ++i)
    {
        Network::IpAddress ip;
        ip.unserialize(readBuffer);
        hostIpAddresses_.push_back(ip);
    }
}

std::ostream& NetworkInfo::operator <<(std::ostream& os) const
{
    os << "["
       << "macAddress=" << macAddress_
       << ", hostIpAddresses=[";
    for (auto ip : hostIpAddresses_)
    {
        os << ip << ",";
    }
    os << "]]";
    return os;
}

bool NetworkInfo::operator ==(const NetworkInfo& info) const
{
    return (macAddress_ == info.macAddress_ &&
            hostIpAddresses_ == info.hostIpAddresses_);
}

void NetworkInfo::update()
{
    updateMacAddress();
    updateIpAddress();
}

void NetworkInfo::updateMacAddress()
{
    std::string addressFile("/sys/class/net/eth0/address");
    std::ifstream ifs(addressFile.c_str());

    if (!ifs.good())
    {
        TRACE_WARNING("Failed to open file: " << addressFile << ", stop reading, try next time." << std::endl);
        return;
    }

    char buffer[128];
    if(ifs.good())
    {
        std::fill(buffer, buffer + 128, 0);
        ifs.getline(buffer, 128);
        std::stringstream ss;
        ss << buffer;
    };

    macAddress_ = buffer;
}

void NetworkInfo::updateIpAddress()
{
    hostIpAddresses_ = Network::NetworkEnv::getLocalIpAddress();
}

}
