#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "DiskUsageInfo.h"
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
class DiskUsageInfoTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(DiskUsageInfoTest, Test)
{
    DiskUsageInfo info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(DiskUsageInfoTest, ReadWrite)
{
	uint64_t startTimeStamp = 1000;
	uint32_t elapseTime = 500;
	DiskUsageInfo info1;
	ShellCommandDfOutput dfOutput;
	dfOutput.setFileSystem("sda");
	dfOutput.setOneKBlock(10000);
	dfOutput.setUsed(6000);
	dfOutput.setAvailable(4000);
	dfOutput.setPecentageUsed(60);
	dfOutput.setMountedOn("/");
	info1.setRootDirUsage(dfOutput);
	dfOutput.setFileSystem("sda");
	dfOutput.setOneKBlock(20000);
	dfOutput.setUsed(7000);
	dfOutput.setAvailable(13000);
	dfOutput.setPecentageUsed(35);
	dfOutput.setMountedOn("/boot");
	info1.setBootInitDirUsage(dfOutput);
	std::cout << info1 << std::endl;
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
	DiskUsageInfo info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	std::cout << info2 << std::endl;
	ASSERT_EQ(info2, info1);
}
#endif
