#include "cpuusageinfo.h"
namespace DataVisualPack {

CpuUsageInfo::CpuUsageInfo()
{

}

int CpuUsageInfo::getGeneralUsage() const
{
    return generalUsage;
}

void CpuUsageInfo::setGeneralUsage(int value)
{
    generalUsage = value;
}

QList<int> CpuUsageInfo::getCoreUsage() const
{
    return coreUsage;
}

void CpuUsageInfo::setCoreUsage(const QList<int> &value)
{
    coreUsage = value;
}

QString CpuUsageInfo::getCpuType() const
{
    return cpuType;
}

void CpuUsageInfo::setCpuType(const QString &value)
{
    cpuType = value;
}

QString CpuUsageInfo::getCpuFrequency() const
{
    return cpuFrequency;
}

void CpuUsageInfo::setCpuFrequency(const QString &value)
{
    cpuFrequency = value;
}

}
