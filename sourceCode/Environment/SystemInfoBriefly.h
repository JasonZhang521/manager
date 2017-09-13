#ifndef SYSTEMINFOBRIEFLY_H
#define SYSTEMINFOBRIEFLY_H
#include "CpuInfoBriefly.h"
#include "MemoryInfoBriefly.h"
#include "NetworkInfo.h"
#include "MiscInfo.h"
#include "DiskUsageInfo.h"
#include "ShellCommandDataType.h"

namespace Environment {

class SystemInfoBriefly
{
    CpuInfoBriefly cpuInfoBriefly_;
    MemoryInfoBriefly memoryInfoBriefly_;
    NetworkInfo networkInfo_;
    MiscInfo miscInfo_;
    DiskUsageInfo diskUsageInfo_;
    CommandOutputString psTop10CpuUsage_;
    CommandOutputString psTop10MemoryUsage_;

public:
    SystemInfoBriefly();
    SystemInfoBriefly(const SystemInfoBriefly& info);
    SystemInfoBriefly& operator =(const SystemInfoBriefly& info);
	void setCpuInfoBriefly(const CpuInfoBriefly& info);
    const CpuInfoBriefly& getCpuInfoBriefly() const;
    const MemoryInfoBriefly& getMemoryInfoBriefly() const;
	void setMemoryInfoBriefly(const MemoryInfoBriefly& info);
    const NetworkInfo& getNetworkInfo() const;
	void setNetworkInfo(const NetworkInfo& info);
    const MiscInfo& getMiscInfo() const;
	void setMiscInfo(const MiscInfo& info);
    const DiskUsageInfo& getDiskUsageInfo() const;
    void setDiskUsageInfo(const DiskUsageInfo& info);
    const CommandOutputString& getPsTop10CpuUsage() const;
    void setPsTop10CpuUsage(const CommandOutputString& info);
    const CommandOutputString& getPsTop10MemoryUsage() const;
    void setPsTop10MemoryUsage(const CommandOutputString& info);

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const SystemInfoBriefly& info) const;

    void update();
};
}

inline std::ostream& operator <<(std::ostream& os, const Environment::SystemInfoBriefly& info)
{
    return info.operator <<(os);
}

#endif // SYSTEMINFOBRIEFLY_H
