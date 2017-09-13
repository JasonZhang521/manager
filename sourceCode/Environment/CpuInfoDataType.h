#ifndef _ENVIRONMENT_CPUINFODATATYPE_H_
#define _ENVIRONMENT_CPUINFODATATYPE_H_
#include <string>
#include <vector>
#include <map>

namespace Environment {

enum CpuInfoType
{
    PROCESSOR,
    VENDOR_ID,
    CPU_FAMILY,
    MODE,
    MODEL_NAME,
    STEPPING,
    CPU_MHZ,
    CACHE_SIZE,
    PHYSICAL_ID,
    SIBLINGS,
    CORE_ID,
    CPU_CORES,
    APICID,
    INITIAL_APICID,
    FPU,
    FPU_EXCEPTION,
    CPUID_LEVEL,
    WP,
    FLAGS,
    BOGOMIPS,
    CLFLUSH_SIZE,
    CACHE_ALIGNMENT,
    ADDRESS_SIZE,
    POWER_MANAGEMENT,
    CPUINFO_INVALID
};

const size_t NUM_OF_CPUINFO_ATTRIBUTE = 24;

using CpuInfoRawData = std::vector<std::string>;
using CpuInfoRawDatas = std::vector<CpuInfoRawData>;

class CpuInfoRawDataAttributeString
{
    static std::vector<std::string> attribute_;
    static std::map<std::string, CpuInfoType> attributeToIndex_;
public:
    static std::string getAttribute(CpuInfoType type);
    static CpuInfoType getAttributeIndex(const std::string& attribute);
};

}
#endif // _ENVIRONMENT_CPUINFODATATYPE_H_
