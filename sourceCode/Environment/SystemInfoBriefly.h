#ifndef SYSTEMINFOBRIEFLY_H
#define SYSTEMINFOBRIEFLY_H
#include "CpuInfoBriefly.h"
#include "MemoryInfoBriefly.h"
#include "NetworkInfo.h"
#include "MiscInfo.h"
#include "DiskUsageInfo.h"
#include "ShellCommandPsTopnCpuUsageOutput.h"
#include "ShellCommandPsTopnMemoryUsageOutput.h"
#include "ShellCommandGenericOutput.h"
#include "ShellCommandDataType.h"

namespace Environment {

class SystemInfoBriefly
{
    CpuInfoBriefly cpuInfoBriefly_;
    MemoryInfoBriefly memoryInfoBriefly_;
    NetworkInfo networkInfo_;
    MiscInfo miscInfo_;
    DiskUsageInfo diskUsageInfo_;
    ShellCommandPsTopnCpuUsageOutputs psTop10CpuUsage_;
    ShellCommandPsTopnMemoryUsageOutputs psTop10MemoryUsage_;
    ShellCommandGenericOutput nvidiaSmiGpuInfo_;
    ShellCommandGenericOutput infiniBandStatInfo_;

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
    const ShellCommandPsTopnCpuUsageOutputs& getPsTop10CpuUsage() const;
    void setPsTop10CpuUsage(const ShellCommandPsTopnCpuUsageOutputs& info);
    const ShellCommandPsTopnMemoryUsageOutputs& getPsTop10MemoryUsage() const;
    void setPsTop10MemoryUsage(const ShellCommandPsTopnMemoryUsageOutputs& info);
    const ShellCommandGenericOutput& getNvidiaSmiGpuInfo() const;
    void setNvidiaSmiGpuInfo( const ShellCommandGenericOutput& nvidiaSmiGpuInfo);
    const ShellCommandGenericOutput& getInfiniBandStatInfo() const;
    void setInfiniBandStatInfo( const ShellCommandGenericOutput& infiniBandStatInfo);


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
