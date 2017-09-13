#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "NetworkInfo.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include <iostream>
#include <string>

#ifdef WIN32
#else
#include <unistd.h>
#endif
using namespace Environment;
using namespace Serialize;
using namespace Network;
class NetworkInfoTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(NetworkInfoTest, Test)
{
    NetworkInfo info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(NetworkInfoTest, ReadWrite)
{
	std::string macAddress("45:E5:32:BC");
	IpAddresses addresses;
	addresses.push_back(IpAddress("168.192.4.5"));
	addresses.push_back(IpAddress("168.192.4.6"));
	NetworkInfo info1;
	info1.setMacAddress(macAddress);
	info1.setHostIpAddresses(addresses);
	std::cout << info1 << std::endl;
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
	NetworkInfo info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	std::cout << info2 << std::endl;
	ASSERT_EQ(info2.getMacAddress(), macAddress);
	ASSERT_EQ(info2.getHostIpAddresses(), addresses);
}
#endif
