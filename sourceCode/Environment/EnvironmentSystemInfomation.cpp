#include "EnvironmentSystemInfomation.h"
#include "CpuInfo.h"
#include "CpuUsage.h"
#include "CpuUsageInfo.h"
#include "CpuInfoBriefly.h"

namespace Environment {
EnvironmentSystemInfomation::EnvironmentSystemInfomation()
{

}

void EnvironmentSystemInfomation::getCpuInfoBriefly(CpuInfoBriefly& cpuInfoBriefly)
{
    CpuUsageInfo cpuUsageInfo(CpuUsage::instance().getCpuUsageEntrys());
    cpuInfoBriefly.setUsage(cpuUsageInfo.getAverageUsage());

    CpuInfo::instance().update();
    CpuInfoRawDatas rawDatas = CpuInfo::instance().getCpuInfoRawData();
    size_t nCpu = rawDatas.size();
    cpuInfoBriefly.setNumOfCpu(nCpu);
    if (nCpu > 0)
    {
        CpuInfoRawData rawData = rawDatas[0];
        cpuInfoBriefly.setModelName(rawData[MODEL_NAME]);
        cpuInfoBriefly.setFrequency(rawData[CPU_MHZ]);
    }
}

void EnvironmentSystemInfomation::getMemoryInfoBriefly(MemoryInfoBriefly& memoryInfoBriefly)
{
    static_cast<void>(memoryInfoBriefly);
}

}
