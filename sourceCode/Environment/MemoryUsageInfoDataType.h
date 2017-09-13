#ifndef _ENVIRONMENT_MEMORYINFODATATYPE_H_
#define _ENVIRONMENT_MEMORYINFODATATYPE_H_
#include <vector>
#include <string>
#include <map>

namespace Environment {

enum MemoryUsageInfoType
{
    MEMTOTAL,
    MEMFREE,
    BUFFERS,
    CACHED,
    SWAPCACHED,
    ACTIVE,
    INACTIVE,
    ACTIVE_ANON,
    INACTIVE_ANON,
    ACTIVE_FILE,
    INACTIVE_FILE,
    UNEVICTABLE,
    MLOCKED,
    SWAPTOTAL,
    SWAPFREE,
    DIRTY,
    WRITEBACK,
    ANONPAGES,
    MAPPED,
    SHMEM,
    SLAB,
    SRECLAIMABLE,
    SUNRECLAIM,
    KERNELSTACK,
    PAGETABLES,
    NFS_UNSTABLE,
    BOUNCE,
    WRITEBACKTMP,
    COMMITLIMIT,
    COMMITTED_AS,
    VMALLOCTOTAL,
    VMALLOCUSED,
    VMALLOCCHUNK,
    HARDWARECORRUPTED,
    ANONHUGEPAGES,
    HUGEPAGES_TOTAL,
    HUGEPAGES_FREE,
    HUGEPAGES_RSVD,
    HUGEPAGES_SURP,
    HUGEPAGESIZE,
    DIRECTMAP4K,
    DIRECTMAP2M,
    DIRECTMAP1G,    
    MEMORYINFO_INVALID
};
const size_t NUM_OF_MEMORY_INFO_ATTRIBUTE = 43;
using MemoryUsageInfoRawData = std::vector<std::string>;

class MemoryUsageInfoRawDataAttributeString
{
    static std::vector<std::string> attribute_;
    static std::map<std::string, MemoryUsageInfoType> attributeToIndex_;
public:
    static std::string getAttribute(MemoryUsageInfoType type);
    static MemoryUsageInfoType getAttributeIndex(const std::string& attribute);
};

}

#endif // _ENVIRONMENT_MEMORYINFODATATYPE_H_
