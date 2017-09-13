#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CpuInfoBriefly.h"
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
class CpuInfoBrieflyTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(CpuInfoBrieflyTest, Test)
{
    CpuInfoBriefly info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(CpuInfoBrieflyTest, ReadWrite)
{
	const uint16_t numOfCpu = 4;
	std::string modelName("Intel");
	std::string frequency("4000M");
	int usage = 80;
	CpuInfoBriefly info1;
	info1.setNumOfCpu(numOfCpu);
	info1.setModelName(modelName);
	info1.setFrequency(frequency);
	info1.setUsage(usage);
	std::cout << info1 << std::endl;
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
	CpuInfoBriefly info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	std::cout << info2 << std::endl;
	ASSERT_EQ(info2.getNumOfCpu(), numOfCpu);
	ASSERT_EQ(info2.getModelName(), modelName);
	ASSERT_EQ(info2.getFrequency(), frequency);
	ASSERT_EQ(info2.getUsage(), usage);
}
#endif
