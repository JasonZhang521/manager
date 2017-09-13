#include "CpuInfo.h"
#include "RemoveCharacter.h"
#include "Trace.h"
#include <sstream>
#include <memory>
namespace Environment {
CpuInfo::CpuInfo()
{
}

std::ostream& CpuInfo::operator << (std::ostream& os) const
{
    os << "[";
    for (CpuInfoRawDatas::const_iterator it = rawDatas_.cbegin(); it != rawDatas_.cend(); ++it)
    {
        const CpuInfoRawData& data = *it;
        size_t index = 0;
        for (CpuInfoRawData::const_iterator jt = data.cbegin(); jt != data.cend(); ++jt)
        {
            os << CpuInfoRawDataAttributeString::getAttribute(static_cast<CpuInfoType>(index))
               << "=" << *jt;
            if (jt != data.cend())
            {
                os << ",";
            }
        }

        if (it != rawDatas_.cend())
        {
            os << "; ";
        }
    }
    os << "]";

    return os;
}

void CpuInfo::update()
{
#ifdef WIN32
#else
    getCpuInfoFromProcCpuInfoFile();
#endif
}

const CpuInfoRawDatas& CpuInfo::getCpuInfoRawData() const
{
    return rawDatas_;
}

CpuInfo& CpuInfo::instance()
{
    static std::unique_ptr<CpuInfo> instance(new CpuInfo());
    return *instance;
}

void CpuInfo::getCpuInfoFromProcCpuInfoFile()
{
    std::string cpuInfofileName("/proc/cpuinfo");
    // for the Linux operation system, the CPU infomation always got from /proc/cpuinfo files
    std::ifstream ifs(cpuInfofileName.c_str());

    if (!ifs.good())
    {
        TRACE_WARNING("Failed to open file: " << cpuInfofileName << ", stop reading, try next time." << std::endl);
        return;
    }

    clear();
    CpuInfoRawData rawData(NUM_OF_CPUINFO_ATTRIBUTE, std::string(""));
    char buffer[2048];
    while(ifs.good())
    {
        std::fill(buffer, buffer + 2048, 0);
        ifs.getline(buffer, 2048);
        std::stringstream ss;
        ss << buffer;
        std::string oneline = ss.str();
        size_t posOfSep = oneline.find(':');
        std::string attribute = oneline.substr(0, posOfSep);
        // delete the front and end space
        RemoveCharacter remover;
        attribute = remover(attribute);
		remover.setCharacter('\t');
		attribute = remover(attribute);
        std::string value = oneline.substr(posOfSep + 1, attribute.size() - posOfSep - 1);
        // delete the front and end space
        value = remover(value);
        remover.setCharacter(' ');
        value = remover(value);
        CpuInfoType cpuInfoType = CpuInfoRawDataAttributeString::getAttributeIndex(attribute);
        if (cpuInfoType != CPUINFO_INVALID)
        {
            rawData[static_cast<size_t>(cpuInfoType)] = value;
        }
        if (cpuInfoType == POWER_MANAGEMENT)
        {
            rawDatas_.push_back(rawData);
        }
    }
}

void CpuInfo::clear()
{
    CpuInfoRawDatas rawDatas;
    rawDatas_.swap(rawDatas);
}

}
