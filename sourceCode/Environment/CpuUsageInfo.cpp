#include "CpuUsageInfo.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "SocketWrapper.h"
#include "Trace.h"

namespace Environment {

CpuUsageInfo::CpuUsageInfo()
{}

CpuUsageInfo::CpuUsageInfo(const CpuUsageEntrys& cpuUsageEntrys)
    :cpuUsageEntrys_(cpuUsageEntrys)
{
}

CpuUsageInfo::CpuUsageInfo(const CpuUsageInfo& info)
 :cpuUsageEntrys_(info.cpuUsageEntrys_)
{

}

CpuUsageInfo& CpuUsageInfo::operator=(const CpuUsageInfo& info)
{
    cpuUsageEntrys_ = info.cpuUsageEntrys_;
    return (*this);
}

unsigned int CpuUsageInfo::getCpuNum() const
{
    TRACE_ENTER();
    if (cpuUsageEntrys_.empty())
    {
        return 0;
    }
    else
    {
        return cpuUsageEntrys_.size() - 1;
    }
}

unsigned int CpuUsageInfo::getTotalUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getTotalUsage();
}

unsigned int CpuUsageInfo::getUserUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getUserUsage();
}

unsigned int CpuUsageInfo::getNiceUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getNiceUsage();
}

unsigned int CpuUsageInfo::getSysUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getSysUsage();
}

unsigned int CpuUsageInfo::getIdleUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getIdleUsage();
}

unsigned int CpuUsageInfo::getIntrUsage(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getIntrUsage();
}
unsigned int CpuUsageInfo::getTotalTime(CpuIndex cpuIndex) const
{
    TRACE_ENTER();
    if (static_cast<unsigned int>(cpuIndex) >= getCpuNum())
    {
        TRACE_ERROR("CpuIndex index error: number of Cpu: " << getCpuNum() << ", cpu index: " << cpuIndex);
        throw std::out_of_range(std::string("Invalid cpu index: "));
    }

    return cpuUsageEntrys_[cpuIndex + 1].getTotalTime();
}

unsigned int CpuUsageInfo::getAverageUsage() const
{
    TRACE_ENTER();
    if (getCpuNum() == 0)
    {
        TRACE_ERROR("number of Cpu is zero!");
        throw std::range_error(std::string("Invalid cpu num: 0"));
    }

    return cpuUsageEntrys_[0].getTotalUsage();
}

unsigned int CpuUsageInfo::getPeakUsage() const
{
    TRACE_ENTER();

    const unsigned int numOfCpu = getCpuNum();
    if (numOfCpu == 0)
    {
        TRACE_ERROR("number of Cpu is zero!");
        throw std::range_error(std::string("Invalid cpu num: 0"));
    }

    unsigned int peakUsage = 0;
    for (unsigned int i = 0; i < numOfCpu; ++i)
    {
        if (cpuUsageEntrys_[i].getTotalUsage() > peakUsage)
        {
            peakUsage = cpuUsageEntrys_[i].getTotalUsage();
        }
    }

    return peakUsage;
}

void CpuUsageInfo::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    TRACE_ENTER();
    if (getCpuNum() == 0)
    {
        TRACE_ERROR("number of Cpu is zero!");
        throw std::range_error(std::string("Invalid cpu num: 0"));
    }

    writeBuffer.write<uint8_t>(static_cast<uint8_t>(cpuUsageEntrys_.size()));
    for (CpuUsageEntrys::const_iterator it = cpuUsageEntrys_.cbegin(); it != cpuUsageEntrys_.cend(); ++it)
    {
        const Environment::CpuUsageEntry& entry = *it;
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getTotalUsage()));
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getUserUsage()));
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getNiceUsage()));
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getSysUsage()));
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getIdleUsage()));
        writeBuffer.write<uint8_t>(static_cast<uint8_t>(entry.getIntrUsage()));
        writeBuffer.write<unsigned int>(entry.getTotalTime());
    }
}

void CpuUsageInfo::unserialize(Serialize::ReadBuffer& readBuffer)
{
    if (readBuffer.getDataSize() == 0)
    {
        TRACE_ERROR("Read buffer size is zero!");
        throw std::range_error(std::string("Invalid Read buffer size: 0"));
    }

    uint8_t size = 0;
    readBuffer.read<uint8_t>(size);

    if (size <= 1)
    {
        TRACE_ERROR("CpuUsageEntrys size if small than 1, at least 2, one is for total, one is for vitual cpu!");
        throw std::runtime_error("CpuUsageEntrys size if small than 1");
    }

    cpuUsageEntrys_ = CpuUsageEntrys(size, CpuUsageEntry());
    for (size_t i = 0; i < static_cast<size_t>(size); i++)
    {
        uint8_t total = 0;
        readBuffer.read<uint8_t>(total);
        cpuUsageEntrys_[i].setTotalUsage(total);

        uint8_t user = 0;
        readBuffer.read<uint8_t>(user);
        cpuUsageEntrys_[i].setUserUsage(user);

        uint8_t nice = 0;
        readBuffer.read<uint8_t>(nice);
        cpuUsageEntrys_[i].setNiceUsage(nice);

        uint8_t sys = 0;
        readBuffer.read<uint8_t>(sys);
        cpuUsageEntrys_[i].setSysUsage(sys);

        uint8_t idle = 0;
        readBuffer.read<uint8_t>(idle);
        cpuUsageEntrys_[i].setIdleUsage(idle);

        uint8_t intr = 0;
        readBuffer.read<uint8_t>(intr);
        cpuUsageEntrys_[i].setIntrUsage(intr);

        uint32_t totalTime = 0;
        readBuffer.read<unsigned int>(totalTime);
        cpuUsageEntrys_[i].setTotalTime(totalTime);
    }
}

std::ostream& CpuUsageInfo::operator <<(std::ostream& os) const
{
    os << "[Cpu usage information:" << cpuUsageEntrys_ << "]";
    return os;
}

}

