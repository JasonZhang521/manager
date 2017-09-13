#include "MemoryUsageInfo.h"
#include "RemoveCharacter.h"
#include "Trace.h"
#include <sstream>
#include <memory>
#include <fstream>
namespace Environment {
MemoryUsageInfo::MemoryUsageInfo()
{

}

std::ostream& MemoryUsageInfo::operator << (std::ostream& os) const
{
    os << "[";
    for (MemoryUsageInfoRawData::const_iterator it = rawData_.cbegin(); it != rawData_.cend(); ++it)
    {
        size_t index = 0;
        os << MemoryUsageInfoRawDataAttributeString::getAttribute(static_cast<MemoryUsageInfoType>(index))
           << "=" << *it;
        os << ",";
    }
    os << "]";

    return os;
}
void MemoryUsageInfo::update()
{
#ifdef WIN32
#else
	getMemoryInfoFromcProcMemoInfoFile();
#endif
}

const MemoryUsageInfoRawData MemoryUsageInfo::getMemoryUsageInfoRawData() const
{
    return rawData_;
}

MemoryUsageInfo& MemoryUsageInfo::instance()
{
    static std::unique_ptr<MemoryUsageInfo> instance(new MemoryUsageInfo());
    return *instance;
}

void MemoryUsageInfo::getMemoryInfoFromcProcMemoInfoFile()
{
    std::string memInfofileName("/proc/meminfo");
    // for the Linux operation system, the memory infomation always got from /proc/meminfo files
    /*
       MemTotal:       65921260 kB
       MemFree:         2862644 kB
       Buffers:          411772 kB
       Cached:         42338600 kB
     */
    std::ifstream ifs(memInfofileName.c_str());

    if (!ifs.good())
    {
        TRACE_WARNING("Failed to open file: " << memInfofileName << ", stop reading, try next time." << std::endl);
        return;
    }

    MemoryUsageInfoRawData rawData(NUM_OF_MEMORY_INFO_ATTRIBUTE, std::string(""));
    RemoveCharacter remover;
    char buffer[512];
    while(ifs.good())
    {
        std::fill(buffer, buffer + 512, 0);
        ifs.getline(buffer, 512);
        std::stringstream ss;
        ss << buffer;
        std::string str = ss.str();
        size_t posOfSep = str.find(':');
        std::string attribute = str.substr(0, posOfSep);
        // delete the front and end space and tab
        attribute = remover.removeMultiCh(attribute, " \t");
        str = str.substr(posOfSep + 1, str.size() - posOfSep - 1);
        // delete the front and end space
        str = remover.removeMultiCh(str, " \t");
        size_t posOfSpace = str.find(' ');
        std::string value = str.substr(0, posOfSpace);
        MemoryUsageInfoType memInfoType = MemoryUsageInfoRawDataAttributeString::getAttributeIndex(attribute);
        if (memInfoType != MEMORYINFO_INVALID)
        {
            rawData[static_cast<size_t>(memInfoType)] = value;
        }
    }
    rawData_.swap(rawData);
}

void MemoryUsageInfo::clear()
{
    MemoryUsageInfoRawData rawData;
    rawData_.swap(rawData);
}

}
