#include "SystemInfoBriefly.h"
#include "Environment.h"
#include "ShellCommandDataType.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace Environment {
SystemInfoBriefly::SystemInfoBriefly()
{

}

SystemInfoBriefly::SystemInfoBriefly(const SystemInfoBriefly& info)
    : cpuInfoBriefly_(info.cpuInfoBriefly_)
    , memoryInfoBriefly_(info.memoryInfoBriefly_)
    , networkInfo_(info.networkInfo_)
    , miscInfo_(info.miscInfo_)
    , diskUsageInfo_(info.diskUsageInfo_)
    , psTop10CpuUsage_(info.psTop10CpuUsage_)
    , psTop10MemoryUsage_(info.psTop10MemoryUsage_)
{

}

SystemInfoBriefly& SystemInfoBriefly::operator =(const SystemInfoBriefly& info)
{
    cpuInfoBriefly_ = info.cpuInfoBriefly_;
    memoryInfoBriefly_ = info.memoryInfoBriefly_;
    networkInfo_ = info.networkInfo_;
    miscInfo_ = info.miscInfo_;
	diskUsageInfo_ = info.diskUsageInfo_;
    psTop10CpuUsage_ = info.psTop10CpuUsage_;
    psTop10MemoryUsage_ = info.psTop10MemoryUsage_;
    return *this;
}

const CpuInfoBriefly& SystemInfoBriefly::getCpuInfoBriefly() const
{
    return cpuInfoBriefly_;
}

void SystemInfoBriefly::setCpuInfoBriefly(const CpuInfoBriefly& info)
{
    cpuInfoBriefly_ = info;
}

const MemoryInfoBriefly& SystemInfoBriefly::getMemoryInfoBriefly() const
{
    return memoryInfoBriefly_;
}

void SystemInfoBriefly::setMemoryInfoBriefly(const MemoryInfoBriefly& info)
{
	memoryInfoBriefly_ = info;
}

const NetworkInfo& SystemInfoBriefly::getNetworkInfo() const
{
    return networkInfo_;
}

void SystemInfoBriefly::setNetworkInfo(const NetworkInfo& info)
{
	networkInfo_ = info;
}

const MiscInfo& SystemInfoBriefly::getMiscInfo() const
{
    return miscInfo_;
}

void SystemInfoBriefly::setMiscInfo(const MiscInfo& info)
{
	miscInfo_ = info;
}

const DiskUsageInfo& SystemInfoBriefly::getDiskUsageInfo() const
{
    return diskUsageInfo_;
}

void SystemInfoBriefly::setDiskUsageInfo(const DiskUsageInfo& info)
{
    diskUsageInfo_ = info;
}

const CommandOutputString& SystemInfoBriefly::getPsTop10CpuUsage() const
{
    return psTop10CpuUsage_;
}

void SystemInfoBriefly::setPsTop10CpuUsage(const CommandOutputString& info)
{
    psTop10CpuUsage_ = info;
}

const CommandOutputString& SystemInfoBriefly::getPsTop10MemoryUsage() const
{
    return psTop10MemoryUsage_;
}

void SystemInfoBriefly::setPsTop10MemoryUsage(const CommandOutputString& info)
{
    psTop10MemoryUsage_ = info;
}

void SystemInfoBriefly::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    cpuInfoBriefly_.serialize(writeBuffer);
    memoryInfoBriefly_.serialize(writeBuffer);
    networkInfo_.serialize(writeBuffer);
    miscInfo_.serialize(writeBuffer);
    diskUsageInfo_.serialize(writeBuffer);

    writeBuffer.write(psTop10CpuUsage_);
    writeBuffer.write(psTop10MemoryUsage_);
}

void SystemInfoBriefly::unserialize(Serialize::ReadBuffer& readBuffer)
{
    cpuInfoBriefly_.unserialize(readBuffer);
    memoryInfoBriefly_.unserialize(readBuffer);
    networkInfo_.unserialize(readBuffer);
    miscInfo_.unserialize(readBuffer);
    diskUsageInfo_.unserialize(readBuffer);
    readBuffer.read(psTop10CpuUsage_);
    readBuffer.read(psTop10MemoryUsage_);
}

std::ostream& SystemInfoBriefly::operator <<(std::ostream& os) const
{
    os << "["
       << "cpuInfoBriefly=" << cpuInfoBriefly_
       << ", memoryInfoBriefly=" << memoryInfoBriefly_
       << ", networkInfo=" << networkInfo_
       << ", miscInfo=" << miscInfo_
       << ", diskUsageInfo" << diskUsageInfo_
       << ", psTop10CpuUsage:\n";
    for (auto str : psTop10CpuUsage_)
    {
        os << str << std::endl;
    }
    os << ", psTop10MemoryUsage:\n";
    for (auto str : psTop10MemoryUsage_)
    {
        os << str << std::endl;
    }
    os << "]";
    return os;
}

bool SystemInfoBriefly::operator ==(const SystemInfoBriefly& info) const
{
    return (cpuInfoBriefly_ == info.cpuInfoBriefly_ &&
            memoryInfoBriefly_ == info.memoryInfoBriefly_ &&
            networkInfo_ == info.networkInfo_ &&
            miscInfo_ == info.miscInfo_ &&
            diskUsageInfo_ == info.diskUsageInfo_);
}

void SystemInfoBriefly::update()
{
    cpuInfoBriefly_.update();
    memoryInfoBriefly_.update();
    networkInfo_.update();
    miscInfo_.update();
    diskUsageInfo_.update();
    psTop10CpuUsage_ = Environment::instance().getShellCmdOutput(ShellCommandType::PsTop10CpuUsage);
    psTop10MemoryUsage_ = Environment::instance().getShellCmdOutput(ShellCommandType::PsTop10MemoryUsage);
}

}
