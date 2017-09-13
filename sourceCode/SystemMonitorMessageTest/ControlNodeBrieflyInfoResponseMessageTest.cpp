#include "ControlNodeBrieflyInfoResponse.h"
#include "SystemInfoBriefly.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>
#include <iostream>

using namespace IpcMessage;
using namespace SystemMonitorMessage;
using namespace Environment;
using namespace Network;
using namespace Serialize;

class ControlNodeBrieflyInfoResponseTest : public ::testing::Test
{
};

TEST_F(ControlNodeBrieflyInfoResponseTest, ReadWrite)
{
    uint64_t startTimeStamp = 1501341215000;
    uint32_t elapseTime = 4858;
    MiscInfo miscInfo;
    miscInfo.setNodeStartTimeStamp(startTimeStamp);
    miscInfo.setElapseTimeFromNodeStart(elapseTime);

	const uint16_t numOfCpu = 4;
    std::string modelName("Intel(R) Core(TM) i7-6700K CPU @ 4.00GHz");
    std::string frequency("4008.000");
	int usage = 80;
	CpuInfoBriefly cpuInfo;
	cpuInfo.setNumOfCpu(numOfCpu);
	cpuInfo.setModelName(modelName);
	cpuInfo.setFrequency(frequency);
	cpuInfo.setUsage(usage);

    const uint64_t memTotal = 2039796;
    const uint64_t memFree = 1318016;
	MemoryInfoBriefly memoryInfo;
	memoryInfo.setMemTotal(memTotal);
	memoryInfo.setMemFree(memFree);

    std::string macAddress("00:0c:29:05:0d:58");
	IpAddresses addresses;
	addresses.push_back(IpAddress("168.192.4.5"));
	addresses.push_back(IpAddress("168.192.4.6"));
	NetworkInfo networkInfo;
	networkInfo.setMacAddress(macAddress);
	networkInfo.setHostIpAddresses(addresses);

	SystemInfoBriefly info;
	info.setMiscInfo(miscInfo);
	info.setCpuInfoBriefly(cpuInfo);
	info.setMemoryInfoBriefly(memoryInfo);
	info.setNetworkInfo(networkInfo);

    ControlNodeBrieflyInfoResponse response;
	response.setSystemInfoBriefly(info);
	std::cout << response << std::endl;

	WriteBuffer wBuffer;
	response.serialize(wBuffer);
    std::cout << wBuffer << std::endl;
    ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	ControlNodeBrieflyInfoResponse newResponse;
	newResponse.unserialize(rBuffer);
	std::cout << newResponse << std::endl;
    ASSERT_EQ(info, newResponse.getSystemInfoBriefly());

    ReadBuffer rBuffer2;
    rBuffer2.setDataSize(wBuffer.getDataSize());
    std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer2.getBuffer()));

    ControlNodeBrieflyInfoResponse newResponse2;
    IIpcMessage& msg = newResponse2;
    msg.unserialize(rBuffer2);
    std::cout << newResponse2 << std::endl;
}
