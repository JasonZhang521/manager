#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MemoryInfoBriefly.h"
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
class MemoryInfoBrieflyTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(MemoryInfoBrieflyTest, Test)
{
    MemoryInfoBriefly info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(MemoryInfoBrieflyTest, ReadWrite)
{
	const uint64_t memTotal = 1024;
	const uint64_t memFree = 512;
	MemoryInfoBriefly info1;
	info1.setMemTotal(memTotal);
	info1.setMemFree(memFree);
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
	MemoryInfoBriefly info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	ASSERT_EQ(info2.getMemTotal(), memTotal);
	ASSERT_EQ(info2.getMemFree(), memFree);
}
#endif
