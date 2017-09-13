#ifndef _ENVIRONMENT_CPUUSAGECALCULATOR_H_
#define _ENVIRONMENT_CPUUSAGECALCULATOR_H_
#include "CpuUsageDataType.h"
#include <functional>

namespace Environment {

class CpuUsageEntryCalculator : public std::unary_function<CpuUsageRawData, CpuUsageEntry>
{
public:
    CpuUsageEntry operator() (const CpuUsageRawData& data);
};

class CpuUsageEntrysCalculator : public std::unary_function<CpuUsageRawDatas, CpuUsageEntrys>
{
public:
    CpuUsageEntrys operator() (const CpuUsageRawDatas& datas);
};

class CpuUsageRawDataDiffCalculator : public std::binary_function<CpuUsageRawData, CpuUsageRawData, CpuUsageRawData>
{
public:
    CpuUsageRawData operator() (const CpuUsageRawData& curData, const CpuUsageRawData& preData);
};

class CpuUsageRawDatasDiffCalculator : public std::binary_function<CpuUsageRawDatas, CpuUsageRawDatas, CpuUsageRawDatas>
{
public:
    CpuUsageRawDatas operator() (const CpuUsageRawDatas& curDatas, const CpuUsageRawDatas& preDatas);
};

}

#endif // _ENVIRONMENT_CPUUSAGECALCULATOR_H_
