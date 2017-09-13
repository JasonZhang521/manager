#ifndef _ENVIRONMENT_MEMORYINFO_H_
#define _ENVIRONMENT_MEMORYINFO_H_
#include "MemoryUsageInfoDataType.h"
#include "Component.h"
#include "Macro.h"

namespace Environment {
class MemoryUsageInfo
{
    MemoryUsageInfoRawData rawData_;
public:
    MemoryUsageInfo();
    std::ostream& operator << (std::ostream&) const;
    void update();
    const MemoryUsageInfoRawData getMemoryUsageInfoRawData() const;
    static MemoryUsageInfo& instance();
private:
    void getMemoryInfoFromcProcMemoInfoFile();
    void clear();
public:
     GETCLASSNAME(MemoryInfo)
};
}

#endif // _ENVIRONMENT_MEMORYINFO_H_
