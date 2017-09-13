#ifndef _ENVIRONMENT_NETWORKINFO_H_
#define _ENVIRONMENT_NETWORKINFO_H_
#include "NetworkEnv.h"
#include "Component.h"
#include "Macro.h"
#include <string>
#include <ostream>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {
class NetworkInfo
{
    std::string macAddress_;
    Network::IpAddresses hostIpAddresses_;

public:
    NetworkInfo();
    NetworkInfo(const NetworkInfo& info);
    NetworkInfo& operator =(const NetworkInfo& info);
    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const NetworkInfo& info) const;

    void update();

	void setMacAddress(const std::string& macAddress) {macAddress_ = macAddress;}
	const std::string& getMacAddress() const {return macAddress_;}
	void setHostIpAddresses(const Network::IpAddresses& hostIpAddresses) {hostIpAddresses_ = hostIpAddresses;}
	const Network::IpAddresses& getHostIpAddresses() const {return hostIpAddresses_;}

private:
    void updateMacAddress();
    void updateIpAddress();

public:
     GETCLASSNAME(NetworkInfo)
};
}


inline std::ostream& operator <<(std::ostream& os, const Environment::NetworkInfo& info)
{
    return info.operator <<(os);
}


#endif // NETWORKINFO_H
