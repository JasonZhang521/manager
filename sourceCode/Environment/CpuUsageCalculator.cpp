#include "CpuUsageCalculator.h"
#include <algorithm>
#include <iostream>
namespace Environment {

CpuUsageEntry CpuUsageEntryCalculator::operator() (const CpuUsageRawData& data)
{
    CpuUsageEntry entry;
    if (data.size() != CPU_USAGE_TYPE_NUMBER)
    {
        return entry;
    }
    else
    {
        uint64_t sum = 0;
        for (CpuUsageRawData::const_iterator it = data.begin(); it != data.end(); ++it)
        {
            sum += *it;
        }
        if (sum != 0)
        {
            entry.setTotalUsage((100 * (sum - data[CPU_IDLE]) + sum / 2) / sum);
            entry.setIdleUsage((100 * data[CPU_IDLE] + sum / 2) / sum);
            entry.setUserUsage((100 * data[CPU_USER] + sum / 2) / sum);
            entry.setNiceUsage((100 * data[CPU_NICE] + sum / 2) / sum);
            entry.setSysUsage((100 * data[CPU_SYS] + sum / 2) / sum);
            entry.setIntrUsage((100 * (data[CPU_IRQ] + data[CPU_SOFTIRQ]) + sum / 2) / sum);
        }

        entry.setTotalTime(sum);
        return entry;
    }
}

CpuUsageEntrys CpuUsageEntrysCalculator::operator() (const CpuUsageRawDatas& datas)
{
    CpuUsageEntrys entrys(datas.size(), CpuUsageEntry());
    std::transform(datas.begin(), datas.end(), entrys.begin(), CpuUsageEntryCalculator());
    return entrys;
}

CpuUsageRawData CpuUsageRawDataDiffCalculator::operator() (const CpuUsageRawData& curData, const CpuUsageRawData& preData)
{
    if (curData.size() == CPU_USAGE_TYPE_NUMBER && preData.size() == CPU_USAGE_TYPE_NUMBER)
    {
        CpuUsageRawData data(CPU_USAGE_TYPE_NUMBER, 0);
        std::transform(curData.begin(), curData.end(), preData.begin(), data.begin(), std::minus<uint64_t>());
        return data;
    }
    else
    {
        return CpuUsageRawData();
    }
}

CpuUsageRawDatas CpuUsageRawDatasDiffCalculator::operator() (const CpuUsageRawDatas& curDatas, const CpuUsageRawDatas& preDatas)
{

    if (curDatas.size() == preDatas.size())
    {
        CpuUsageRawData data(CPU_USAGE_TYPE_NUMBER, 0);
        CpuUsageRawDatas datas(curDatas.size(), data);
        std::transform(curDatas.begin(), curDatas.end(), preDatas.begin(), datas.begin(), CpuUsageRawDataDiffCalculator());
        return datas;
    }
    else
    {
        return CpuUsageRawDatas();
    }
}

}
