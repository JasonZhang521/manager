#include "CpuInfoDataType.h"
namespace Environment {

std::vector<std::string> CpuInfoRawDataAttributeString::attribute_ =
{
    std::string("processor"),
    std::string("vendor_id"),
    std::string("cpu family"),
    std::string("model"),
    std::string("model name"),
    std::string("stepping"),
    std::string("cpu MHz"),
    std::string("cache size"),
    std::string("physical id"),
    std::string("siblings"),
    std::string("core id"),
    std::string("cpu cores"),
    std::string("apicid"),
    std::string("initial apicid"),
    std::string("fpu"),
    std::string("fpu_exception"),
    std::string("cpuid level"),
    std::string("wp"),
    std::string("flags"),
    std::string("bogomips"),
    std::string("clflush size"),
    std::string("cache_alignment"),
    std::string("address sizes"),
    std::string("power management")
};

std::map<std::string, CpuInfoType> CpuInfoRawDataAttributeString::attributeToIndex_ =
{
    {std::string("processor"), PROCESSOR},
    {std::string("vendor_id"), VENDOR_ID},
    {std::string("cpu family"), CPU_FAMILY},
    {std::string("model"), MODE},
    {std::string("model name"), MODEL_NAME},
    {std::string("stepping"), STEPPING},
    {std::string("cpu MHz"), CPU_MHZ},
    {std::string("cache size"), CACHE_SIZE},
    {std::string("physical id"), PHYSICAL_ID},
    {std::string("siblings"), SIBLINGS},
    {std::string("core id"), CORE_ID},
    {std::string("cpu cores"), CPU_CORES},
    {std::string("apicid"), APICID},
    {std::string("initial apicid"), INITIAL_APICID},
    {std::string("fpu"), FPU},
    {std::string("fpu_exception"), FPU_EXCEPTION},
    {std::string("cpuid level"), CPUID_LEVEL},
    {std::string("wp"), WP},
    {std::string("flags"), FLAGS},
    {std::string("bogomips"), BOGOMIPS},
    {std::string("clflush size"), CLFLUSH_SIZE},
    {std::string("cache_alignment"), CACHE_ALIGNMENT},
    {std::string("address sizes"), ADDRESS_SIZE},
    {std::string("power management"), POWER_MANAGEMENT}
};


std::string CpuInfoRawDataAttributeString::getAttribute(CpuInfoType type)
{
    return attribute_[static_cast<size_t>(type)];
}

CpuInfoType CpuInfoRawDataAttributeString::getAttributeIndex(const std::string& attribute)
{
    std::map<std::string, CpuInfoType>::iterator it = attributeToIndex_.find(attribute);
    if (it != attributeToIndex_.end())
    {
        return it->second;
    }
    else
    {
        return CPUINFO_INVALID;
    }
}

}

