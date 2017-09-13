#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MemoryUsageInfo.h"
#include "MemoryUsageInfoDataType.h"
#include <iostream>

#ifdef WIN32
#else
#include <unistd.h>
#endif
using namespace Environment;

class MemoryUsageInfoTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(MemoryUsageInfoTest, Test)
{
    MemoryUsageInfo usage;
	sleep(3);
    usage.update();
	const MemoryUsageInfoRawData& rawData = usage.getMemoryUsageInfoRawData();
    for (unsigned int i = 0; i < NUM_OF_MEMORY_INFO_ATTRIBUTE; ++i)
	{
		std::cout << MemoryUsageInfoRawDataAttributeString::getAttribute(static_cast<MemoryUsageInfoType>(i)) << ":" << rawData[i] << std::endl;
	}
    std::cout << std::endl;
	sleep(3);
	usage.update();
    for (unsigned int i = 0; i < NUM_OF_MEMORY_INFO_ATTRIBUTE; ++i)
	{
		std::cout << MemoryUsageInfoRawDataAttributeString::getAttribute(static_cast<MemoryUsageInfoType>(i)) << ":" << rawData[i] << std::endl;
	}
}

#endif
