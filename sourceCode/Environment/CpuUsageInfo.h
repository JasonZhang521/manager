#ifndef _ENVIRONMENT_CPUUSAGEINFO_H_
#define _ENVIRONMENT_CPUUSAGEINFO_H_
#include "CpuUsageDataType.h"
#include "Component.h"
#include "Macro.h"

namespace Serialize {
    class WriteBuffer;
    class ReadBuffer;
}

namespace Environment {

enum CpuIndex
{
    cpu0 = 0,
    cpu1,
    cpu2,
    cpu3,
    cpu4,
    cpu5,
    cpu6,
    cpu7,
    cpu8,
    cpu9,
    cpu10,
    cpu11,
    cpu12,
    cpu13,
    cpu14,
    cpu15,
    cpu16,
    cpu17,
    cpu18,
    cpu19,
    cpu20,
    cpu21,
    cpu22,
    cpu23,
    cpu24,
    cpu25,
    cpu26,
    cpu27,
    cpu28,
    cpu29,
    cpu30,
    cpu31,
};

class CpuUsageInfo
{
    CpuUsageEntrys cpuUsageEntrys_;
public:
    CpuUsageInfo();
    CpuUsageInfo(const CpuUsageEntrys& cpuUsageEntrys);
    CpuUsageInfo(const CpuUsageInfo& info);
    CpuUsageInfo& operator=(const CpuUsageInfo& info);
    unsigned int getCpuNum() const;
    unsigned int getTotalUsage(CpuIndex cpuIndex) const;
    unsigned int getUserUsage(CpuIndex cpuIndex) const;
    unsigned int getNiceUsage(CpuIndex cpuIndex) const;
    unsigned int getSysUsage(CpuIndex cpuIndex) const;
    unsigned int getIdleUsage(CpuIndex cpuIndex) const;
    unsigned int getIntrUsage(CpuIndex cpuIndex) const;
    unsigned int getTotalTime(CpuIndex cpuIndex) const;
    unsigned int getAverageUsage() const;
    unsigned int getPeakUsage() const;

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);

    std::ostream& operator <<(std::ostream& os) const;

public:
     GETCLASSNAME(CpuUsageInfo)
};

inline std::ostream& operator <<(std::ostream& os, const CpuUsageInfo& cpuUsageInfo)
{
    return cpuUsageInfo.operator <<(os);
}

}

#endif // _ENVIRONMENT_CPUUSAGEINFO_H_
