#include "MemoryUsageInfoDataType.h"
namespace Environment {
std::vector<std::string> MemoryUsageInfoRawDataAttributeString::attribute_ =
{
    std::string("MemTotal"),
    std::string("MemFree"),
    std::string("Buffers"),
    std::string("Cached"),
    std::string("SwapCached"),
    std::string("Active"),
    std::string("Inactive"),
    std::string("Active(anon)"),
    std::string("Inactive(anon)"),
    std::string("Active(file)"),
    std::string("Inactive(file)"),
    std::string("Unevictable"),
    std::string("Mlocked"),
    std::string("SwapTotal"),
    std::string("SwapFree"),
    std::string("Dirty"),
    std::string("Writeback"),
    std::string("AnonPages"),
    std::string("Mapped"),
    std::string("Shmem"),
    std::string("Slab"),
    std::string("SReclaimable"),
    std::string("SUnreclaim"),
    std::string("KernelStack"),
    std::string("PageTables"),
    std::string("NFS_Unstable"),
    std::string("Bounce"),
    std::string("WritebackTmp"),
    std::string("CommitLimit"),
    std::string("Committed_AS"),
    std::string("VmallocTotal"),
    std::string("VmallocUsed"),
    std::string("VmallocChunk"),
    std::string("HardwareCorrupted"),
    std::string("AnonHugePages"),
    std::string("HugePages_Total"),
    std::string("HugePages_Free"),
    std::string("HugePages_Rsvd"),
    std::string("HugePages_Surp"),
    std::string("Hugepagesize"),
    std::string("DirectMap4k"),
    std::string("DirectMap2M"),
    std::string("DirectMap1G"),
    std::string("MemoryInfo_Invalid")
};

std::map<std::string, MemoryUsageInfoType> MemoryUsageInfoRawDataAttributeString::attributeToIndex_ =
{
    {std::string("MemTotal"), MEMTOTAL},
    {std::string("MemFree"), MEMFREE},
    {std::string("Buffers"), BUFFERS},
    {std::string("Cached"), CACHED},
    {std::string("SwapCached"), SWAPCACHED},
    {std::string("Active"), ACTIVE},
    {std::string("Inactive"), INACTIVE},
    {std::string("Active(anon)"), ACTIVE_ANON},
    {std::string("Inactive(anon)"), INACTIVE_ANON},
    {std::string("Active(file)"), ACTIVE_FILE},
    {std::string("Inactive(file)"), INACTIVE_FILE},
    {std::string("Unevictable"), UNEVICTABLE},
    {std::string("Mlocked"), MLOCKED},
    {std::string("SwapTotal"), SWAPTOTAL},
    {std::string("SwapFree"), SWAPFREE},
    {std::string("Dirty"), DIRTY},
    {std::string("Writeback"), WRITEBACK},
    {std::string("AnonPages"), ANONPAGES},
    {std::string("Mapped"), MAPPED},
    {std::string("Shmem"), SHMEM},
    {std::string("Slab"), SLAB},
    {std::string("SReclaimable"), SRECLAIMABLE},
    {std::string("SUnreclaim"), SUNRECLAIM},
    {std::string("KernelStack"), KERNELSTACK},
    {std::string("PageTables"), PAGETABLES},
    {std::string("NFS_Unstable"), NFS_UNSTABLE},
    {std::string("Bounce"), BOUNCE},
    {std::string("WritebackTmp"), WRITEBACKTMP},
    {std::string("CommitLimit"), COMMITLIMIT},
    {std::string("Committed_AS"), COMMITTED_AS},
    {std::string("VmallocTotal"), VMALLOCTOTAL},
    {std::string("VmallocUsed"), VMALLOCUSED},
    {std::string("VmallocChunk"), VMALLOCCHUNK},
    {std::string("HardwareCorrupted"), HARDWARECORRUPTED},
    {std::string("AnonHugePages"), ANONHUGEPAGES},
    {std::string("HugePages_Total"), HUGEPAGES_TOTAL},
    {std::string("HugePages_Free"), HUGEPAGES_FREE},
    {std::string("HugePages_Rsvd"), HUGEPAGES_RSVD},
    {std::string("HugePages_Surp"), HUGEPAGES_SURP},
    {std::string("Hugepagesize"), HUGEPAGESIZE},
    {std::string("DirectMap4k"), DIRECTMAP4K},
    {std::string("DirectMap2M"), DIRECTMAP2M},
    {std::string("DirectMap1G"), DIRECTMAP1G}
};

std::string MemoryUsageInfoRawDataAttributeString::getAttribute(MemoryUsageInfoType type)
{
   return attribute_[static_cast<size_t>(type)];
}

MemoryUsageInfoType MemoryUsageInfoRawDataAttributeString::getAttributeIndex(const std::string& attribute)
{
    std::map<std::string, MemoryUsageInfoType>::iterator it = attributeToIndex_.find(attribute);
    if (it != attributeToIndex_.end())
    {
        return it->second;
    }
    else
    {
        return MEMORYINFO_INVALID;
    }
}

}
