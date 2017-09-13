#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CpuUsage.h"
#include <iostream>

#ifdef WIN32
#else
#include <unistd.h>
#endif
using namespace Environment;

class CpuUsageTest : public ::testing::Test
{
};

#ifdef WIN32
#else

TEST_F(CpuUsageTest, Test)
{
    CpuUsage usage;
	sleep(3);
    usage.update();	
    const CpuUsageEntrys& entrys = usage.getCpuUsageEntrys();
	const CpuUsageRawDatas& rawDatas = usage.getCpuUsageRawDatas();
	for (CpuUsageEntrys::const_iterator it = entrys.cbegin(); it != entrys.cend(); ++it)
	{
        std::cout << *it << std::endl;
	}
    std::cout << std::endl;
	for (CpuUsageRawDatas::const_iterator it = rawDatas.cbegin(); it != rawDatas.cend(); ++it)
	{
		for (CpuUsageRawData::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt)
		{
			std::cout << *jt << " ";
		}
		std::cout << std::endl;
	}
	sleep(3);
	usage.update();
	for (CpuUsageEntrys::const_iterator it = entrys.cbegin(); it != entrys.cend(); ++it)
	{
        std::cout << *it << std::endl;
	}
    std::cout << std::endl;
	for (CpuUsageRawDatas::const_iterator it = rawDatas.cbegin(); it != rawDatas.cend(); ++it)
	{
		for (CpuUsageRawData::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt)
		{
			std::cout << *jt << " ";
		}
		std::cout << std::endl;
	}
}

#endif
