#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MiscInfo.h"
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
class MiscInfoTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(MiscInfoTest, Test)
{
    MiscInfo info;
	usleep(3000);
    info.update();
	std::cout << info << std::endl;
	usleep(3000);
	info.update();
	std::cout << info << std::endl;
}

TEST_F(MiscInfoTest, ReadWrite)
{
	uint64_t startTimeStamp = 1000;
	uint32_t elapseTime = 500;
	MiscInfo info1;
	info1.setNodeStartTimeStamp(startTimeStamp);
	info1.setElapseTimeFromNodeStart(elapseTime);
	std::cout << info1 << std::endl;
	WriteBuffer wBuffer;
	info1.serialize(wBuffer);
	MiscInfo info2;
	ReadBuffer rBuffer;
	rBuffer.setDataSize(wBuffer.getDataSize());
	std::copy(reinterpret_cast<char*>(wBuffer.getBuffer()), reinterpret_cast<char*>(wBuffer.getBuffer()) + wBuffer.getDataSize(), reinterpret_cast<char*>(rBuffer.getBuffer()));
	info2.unserialize(rBuffer);
	std::cout << info2 << std::endl;
	ASSERT_EQ(info2.getNodeStartTimeStamp(), startTimeStamp);
	ASSERT_EQ(info2.getElapseTimeFromNodeStart(), elapseTime);
}
#endif
