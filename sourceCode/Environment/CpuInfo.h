#ifndef _ENVIRONMENT_CPUINFO_H_
#define _ENVIRONMENT_CPUINFO_H_
#include "CpuInfoDataType.h"
#include "Component.h"
#include "Macro.h"
#include <ostream>

namespace Environment {
class CpuInfo
{
    CpuInfoRawDatas rawDatas_;
public:
    CpuInfo();
    std::ostream& operator << (std::ostream&) const;
    void update();
    const CpuInfoRawDatas& getCpuInfoRawData() const;
    static CpuInfo& instance();
private:
    void getCpuInfoFromProcCpuInfoFile();
    void clear();

public:
     GETCLASSNAME(CpuInfo)
};

}

inline std::ostream& operator << (std::ostream& os, const Environment::CpuInfo& cpuInfo)
{
    return cpuInfo.operator <<(os);
    return os;
}

#endif // CPUINFO_H
