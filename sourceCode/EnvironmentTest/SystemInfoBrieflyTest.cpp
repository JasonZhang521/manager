#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "SystemInfoBriefly.h"
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
class SystemInfoBrieflyTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(SystemInfoBrieflyTest, Test)
{
    SystemInfoBriefly info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(SystemInfoBrieflyTest, ReadWrite)
{
	uint64_t startTimeStamp = 1000;
	uint32_t elapseTime = 500;
    MiscInfo miscInfo;
    miscInfo.setNodeStartTimeStamp(startTimeStamp);
    miscInfo.setElapseTimeFromNodeStart(elapseTime);

	const uint16_t numOfCpu = 4;
	std::string modelName("Intel");
	std::string frequency("4000M");
	int usage = 80;
	CpuInfoBriefly cpuInfo;
	cpuInfo.setNumOfCpu(numOfCpu);
	cpuInfo.setModelName(modelName);
	cpuInfo.setFrequency(frequency);
	cpuInfo.setUsage(usage);

	const uint64_t memTotal = 1024;
	const uint64_t memFree = 512;
	MemoryInfoBriefly memoryInfo;
	memoryInfo.setMemTotal(memTotal);
	memoryInfo.setMemFree(memFree);

	std::string macAddress("45:E5:32:BC");
	IpAddresses addresses;
	addresses.push_back(IpAddress("168.192.4.5"));
	addresses.push_back(IpAddress("168.192.4.6"));
	NetworkInfo networkInfo;
	networkInfo.setMacAddress(macAddress);
	networkInfo.setHostIpAddresses(addresses);

	SystemInfoBriefly info1;
	info1.setMiscInfo(miscInfo);
	info1.setCpuInfoBriefly(cpuInfo);
	info1.setMemoryInfoBriefly(memoryInfo);
	info1.setNetworkInfo(networkInfo);
	
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
    SystemInfoBriefly info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	ASSERT_EQ(info1, info2);
}
#endif
