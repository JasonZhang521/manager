#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CpuUsageDataType.h"
#include "CpuUsageCalculator.h"
#include "Random.h"

using namespace Environment;

class CpuUsageCalculatorTest : public ::testing::Test
{
};

TEST_F(CpuUsageCalculatorTest, CpuUsageEntryCalculator)
{
    CpuUsageEntryCalculator calculator;
	CpuUsageRawData rawEntry(CPU_USAGE_TYPE_NUMBER, 0);
	rawEntry[CpuUsageType::CPU_USER] = 7;
	rawEntry[CpuUsageType::CPU_NICE] = 8;
	rawEntry[CpuUsageType::CPU_SYS] = 9;
	rawEntry[CpuUsageType::CPU_IDLE] = 10;
	rawEntry[CpuUsageType::CPU_IOWAIT] = 11;
	rawEntry[CpuUsageType::CPU_IRQ] = 12;
	rawEntry[CpuUsageType::CPU_SOFTIRQ] = 13;
	rawEntry[CpuUsageType::CPU_STEALSTOLEN] = 14;
	rawEntry[CpuUsageType::CPU_GUEST] = 16;

	CpuUsageEntry usageEntry = calculator(rawEntry);
	ASSERT_EQ(90, usageEntry.getTotalUsage());
	ASSERT_EQ(7, usageEntry.getUserUsage());
	ASSERT_EQ(8, usageEntry.getNiceUsage());
	ASSERT_EQ(9, usageEntry.getSysUsage());
	ASSERT_EQ(10, usageEntry.getIdleUsage());
	ASSERT_EQ(25, usageEntry.getIntrUsage());
	ASSERT_EQ(100, usageEntry.getTotalTime());
}

TEST_F(CpuUsageCalculatorTest, CpuUsageEntrysCalculator)
{
    CpuUsageEntrysCalculator calculator;
	CpuUsageRawDatas rawEntrys(2, CpuUsageRawData(CPU_USAGE_TYPE_NUMBER, 0));
	CpuUsageRawData rawEntry(CPU_USAGE_TYPE_NUMBER, 0);
	rawEntry[CpuUsageType::CPU_USER] = 7;
	rawEntry[CpuUsageType::CPU_NICE] = 8;
	rawEntry[CpuUsageType::CPU_SYS] = 9;
	rawEntry[CpuUsageType::CPU_IDLE] = 10;
	rawEntry[CpuUsageType::CPU_IOWAIT] = 11;
	rawEntry[CpuUsageType::CPU_IRQ] = 12;
	rawEntry[CpuUsageType::CPU_SOFTIRQ] = 13;
	rawEntry[CpuUsageType::CPU_STEALSTOLEN] = 14;
	rawEntry[CpuUsageType::CPU_GUEST] = 16;
    rawEntrys[0] = rawEntry;

	rawEntry[CpuUsageType::CPU_USER] = 16;
	rawEntry[CpuUsageType::CPU_NICE] = 14;
	rawEntry[CpuUsageType::CPU_SYS] = 13;
	rawEntry[CpuUsageType::CPU_IDLE] = 12;
	rawEntry[CpuUsageType::CPU_IOWAIT] = 11;
	rawEntry[CpuUsageType::CPU_IRQ] = 10;
	rawEntry[CpuUsageType::CPU_SOFTIRQ] = 9;
	rawEntry[CpuUsageType::CPU_STEALSTOLEN] = 8;
	rawEntry[CpuUsageType::CPU_GUEST] = 7;
    rawEntrys[1] = rawEntry;


	CpuUsageEntrys usageEntrys = calculator(rawEntrys);
	ASSERT_EQ(90, usageEntrys[0].getTotalUsage());
	ASSERT_EQ(7, usageEntrys[0].getUserUsage());
	ASSERT_EQ(8, usageEntrys[0].getNiceUsage());
	ASSERT_EQ(9, usageEntrys[0].getSysUsage());
	ASSERT_EQ(10, usageEntrys[0].getIdleUsage());
	ASSERT_EQ(25, usageEntrys[0].getIntrUsage());
	ASSERT_EQ(100, usageEntrys[0].getTotalTime());

	ASSERT_EQ(88, usageEntrys[1].getTotalUsage());
	ASSERT_EQ(16, usageEntrys[1].getUserUsage());
	ASSERT_EQ(14, usageEntrys[1].getNiceUsage());
	ASSERT_EQ(13, usageEntrys[1].getSysUsage());
	ASSERT_EQ(12, usageEntrys[1].getIdleUsage());
	ASSERT_EQ(19, usageEntrys[1].getIntrUsage());
	ASSERT_EQ(100, usageEntrys[1].getTotalTime());
}

TEST_F(CpuUsageCalculatorTest, CpuUsageRawDataDiffCalculator)
{
	CpuUsageRawDataDiffCalculator calculator;

	CpuUsageRawData curRawData(CPU_USAGE_TYPE_NUMBER, 0);
	curRawData[CpuUsageType::CPU_USER] = 1;
	curRawData[CpuUsageType::CPU_NICE] = 2;
	curRawData[CpuUsageType::CPU_SYS] = 3;
	curRawData[CpuUsageType::CPU_IDLE] = 4;
	curRawData[CpuUsageType::CPU_IOWAIT] = 5;
	curRawData[CpuUsageType::CPU_IRQ] = 6;
	curRawData[CpuUsageType::CPU_SOFTIRQ] = 7;
	curRawData[CpuUsageType::CPU_STEALSTOLEN] = 8;
	curRawData[CpuUsageType::CPU_GUEST] = 9;

	CpuUsageRawData preRawData(CPU_USAGE_TYPE_NUMBER, 0);
	preRawData[CpuUsageType::CPU_USER] = 1;
	preRawData[CpuUsageType::CPU_NICE] = 1;
	preRawData[CpuUsageType::CPU_SYS] = 1;
	preRawData[CpuUsageType::CPU_IDLE] = 1;
	preRawData[CpuUsageType::CPU_IOWAIT] = 1;
	preRawData[CpuUsageType::CPU_IRQ] = 1;
	preRawData[CpuUsageType::CPU_SOFTIRQ] = 1;
	preRawData[CpuUsageType::CPU_STEALSTOLEN] = 1;
	preRawData[CpuUsageType::CPU_GUEST] = 1;

	CpuUsageRawData diffRawData = calculator(curRawData, preRawData);

	ASSERT_EQ(0, diffRawData[CpuUsageType::CPU_USER]);
	ASSERT_EQ(1, diffRawData[CpuUsageType::CPU_NICE]);
	ASSERT_EQ(2, diffRawData[CpuUsageType::CPU_SYS]);
	ASSERT_EQ(3, diffRawData[CpuUsageType::CPU_IDLE]);
	ASSERT_EQ(4, diffRawData[CpuUsageType::CPU_IOWAIT]);
	ASSERT_EQ(5, diffRawData[CpuUsageType::CPU_IRQ]);
	ASSERT_EQ(6, diffRawData[CpuUsageType::CPU_SOFTIRQ]);
	ASSERT_EQ(7, diffRawData[CpuUsageType::CPU_STEALSTOLEN]);
	ASSERT_EQ(8, diffRawData[CpuUsageType::CPU_GUEST]);
}

TEST_F(CpuUsageCalculatorTest, CpuUsageRawDatasDiffCalculator)
{
	CpuUsageRawDatasDiffCalculator calculator;

	CpuUsageRawDatas curRawDatas(2, CpuUsageRawData(CPU_USAGE_TYPE_NUMBER, 0));
	CpuUsageRawData curRawData(CPU_USAGE_TYPE_NUMBER, 0);
	curRawData[CpuUsageType::CPU_USER] = 1;
	curRawData[CpuUsageType::CPU_NICE] = 2;
	curRawData[CpuUsageType::CPU_SYS] = 3;
	curRawData[CpuUsageType::CPU_IDLE] = 4;
	curRawData[CpuUsageType::CPU_IOWAIT] = 5;
	curRawData[CpuUsageType::CPU_IRQ] = 6;
	curRawData[CpuUsageType::CPU_SOFTIRQ] = 7;
	curRawData[CpuUsageType::CPU_STEALSTOLEN] = 8;
	curRawData[CpuUsageType::CPU_GUEST] = 9;

	curRawDatas[0] = curRawData;

	curRawData[CpuUsageType::CPU_USER] = 9;
	curRawData[CpuUsageType::CPU_NICE] = 9;
	curRawData[CpuUsageType::CPU_SYS] = 9;
	curRawData[CpuUsageType::CPU_IDLE] = 9;
	curRawData[CpuUsageType::CPU_IOWAIT] = 9;
	curRawData[CpuUsageType::CPU_IRQ] = 9;
	curRawData[CpuUsageType::CPU_SOFTIRQ] = 9;
	curRawData[CpuUsageType::CPU_STEALSTOLEN] = 9;
	curRawData[CpuUsageType::CPU_GUEST] = 9;

	curRawDatas[1] = curRawData;

	CpuUsageRawDatas preRawDatas(2, CpuUsageRawData(CPU_USAGE_TYPE_NUMBER, 0));
	CpuUsageRawData preRawData(CPU_USAGE_TYPE_NUMBER, 0);
	preRawData[CpuUsageType::CPU_USER] = 1;
	preRawData[CpuUsageType::CPU_NICE] = 1;
	preRawData[CpuUsageType::CPU_SYS] = 1;
	preRawData[CpuUsageType::CPU_IDLE] = 1;
	preRawData[CpuUsageType::CPU_IOWAIT] = 1;
	preRawData[CpuUsageType::CPU_IRQ] = 1;
	preRawData[CpuUsageType::CPU_SOFTIRQ] = 1;
	preRawData[CpuUsageType::CPU_STEALSTOLEN] = 1;
	preRawData[CpuUsageType::CPU_GUEST] = 1;

    preRawDatas[0] = preRawData;

	preRawData[CpuUsageType::CPU_USER] = 1;
	preRawData[CpuUsageType::CPU_NICE] = 1;
	preRawData[CpuUsageType::CPU_SYS] = 1;
	preRawData[CpuUsageType::CPU_IDLE] = 1;
	preRawData[CpuUsageType::CPU_IOWAIT] = 1;
	preRawData[CpuUsageType::CPU_IRQ] = 1;
	preRawData[CpuUsageType::CPU_SOFTIRQ] = 1;
	preRawData[CpuUsageType::CPU_STEALSTOLEN] = 1;
	preRawData[CpuUsageType::CPU_GUEST] = 1;

    preRawDatas[1] = preRawData;


	CpuUsageRawDatas diffRawDatas = calculator(curRawDatas, preRawDatas);

	ASSERT_EQ(0, diffRawDatas[0][CpuUsageType::CPU_USER]);
	ASSERT_EQ(1, diffRawDatas[0][CpuUsageType::CPU_NICE]);
	ASSERT_EQ(2, diffRawDatas[0][CpuUsageType::CPU_SYS]);
	ASSERT_EQ(3, diffRawDatas[0][CpuUsageType::CPU_IDLE]);
	ASSERT_EQ(4, diffRawDatas[0][CpuUsageType::CPU_IOWAIT]);
	ASSERT_EQ(5, diffRawDatas[0][CpuUsageType::CPU_IRQ]);
	ASSERT_EQ(6, diffRawDatas[0][CpuUsageType::CPU_SOFTIRQ]);
	ASSERT_EQ(7, diffRawDatas[0][CpuUsageType::CPU_STEALSTOLEN]);
	ASSERT_EQ(8, diffRawDatas[0][CpuUsageType::CPU_GUEST]);

	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_USER]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_NICE]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_SYS]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_IDLE]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_IOWAIT]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_IRQ]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_SOFTIRQ]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_STEALSTOLEN]);
	ASSERT_EQ(8, diffRawDatas[1][CpuUsageType::CPU_GUEST]);
}
