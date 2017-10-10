#include "SystemInfoBriefly.h"
#include "Environment.h"
#include "ShellCommandDataType.h"
#include "ShellCommandOutputParse.h"
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
    , nvidiaSmiGpuInfo_(info.nvidiaSmiGpuInfo_)
    , infiniBandStatInfo_(info.infiniBandStatInfo_)
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
    nvidiaSmiGpuInfo_ = info.nvidiaSmiGpuInfo_;
    infiniBandStatInfo_ = info.infiniBandStatInfo_;
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

const ShellCommandPsTopnCpuUsageOutputs& SystemInfoBriefly::getPsTop10CpuUsage() const
{
    return psTop10CpuUsage_;
}

void SystemInfoBriefly::setPsTop10CpuUsage(const ShellCommandPsTopnCpuUsageOutputs& info)
{
    psTop10CpuUsage_ = info;
}

const ShellCommandPsTopnMemoryUsageOutputs& SystemInfoBriefly::getPsTop10MemoryUsage() const
{
    return psTop10MemoryUsage_;
}

void SystemInfoBriefly::setPsTop10MemoryUsage(const ShellCommandPsTopnMemoryUsageOutputs& info)
{
    psTop10MemoryUsage_ = info;
}

const ShellCommandGenericOutput& SystemInfoBriefly::getNvidiaSmiGpuInfo() const
{
    return nvidiaSmiGpuInfo_;
}

void SystemInfoBriefly::setNvidiaSmiGpuInfo( const ShellCommandGenericOutput& nvidiaSmiGpuInfo)
{
    nvidiaSmiGpuInfo_ = nvidiaSmiGpuInfo;
}

const ShellCommandGenericOutput& SystemInfoBriefly::getInfiniBandStatInfo() const
{
    return infiniBandStatInfo_;
}

void SystemInfoBriefly::setInfiniBandStatInfo( const ShellCommandGenericOutput& infiniBandStatInfo)
{
    infiniBandStatInfo_ = infiniBandStatInfo;
}

void SystemInfoBriefly::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    cpuInfoBriefly_.serialize(writeBuffer);
    memoryInfoBriefly_.serialize(writeBuffer);
    networkInfo_.serialize(writeBuffer);
    miscInfo_.serialize(writeBuffer);
    diskUsageInfo_.serialize(writeBuffer);
    writeBuffer.write(static_cast<uint8_t>(psTop10CpuUsage_.size()));
    for (size_t i = 0; i < psTop10CpuUsage_.size(); ++i)
    {
        psTop10CpuUsage_[i].serialize(writeBuffer);
    }
    writeBuffer.write(static_cast<uint8_t>(psTop10MemoryUsage_.size()));
    for (size_t i = 0; i < psTop10MemoryUsage_.size(); ++i)
    {
        psTop10MemoryUsage_[i].serialize(writeBuffer);
    }
    nvidiaSmiGpuInfo_.serialize(writeBuffer);
    infiniBandStatInfo_.serialize(writeBuffer);
}

void SystemInfoBriefly::unserialize(Serialize::ReadBuffer& readBuffer)
{
    cpuInfoBriefly_.unserialize(readBuffer);
    memoryInfoBriefly_.unserialize(readBuffer);
    networkInfo_.unserialize(readBuffer);
    miscInfo_.unserialize(readBuffer);
    diskUsageInfo_.unserialize(readBuffer);

    uint8_t size = 0;
    readBuffer.read(size);
    psTop10CpuUsage_.clear();
    for (uint8_t i = 0; i < size; ++i)
    {
        ShellCommandPsTopnCpuUsageOutput output;
        output.unserialize(readBuffer);
        psTop10CpuUsage_.push_back(output);
    }

    readBuffer.read(size);
    psTop10MemoryUsage_.clear();
    for (uint8_t i = 0; i < size; ++i)
    {
        ShellCommandPsTopnMemoryUsageOutput output;
        output.unserialize(readBuffer);
        psTop10MemoryUsage_.push_back(output);
    }

    nvidiaSmiGpuInfo_.unserialize(readBuffer);
    infiniBandStatInfo_.unserialize(readBuffer);
}

std::ostream& SystemInfoBriefly::operator <<(std::ostream& os) const
{
    os << "["
       << "cpuInfoBriefly=" << cpuInfoBriefly_
       << ", memoryInfoBriefly=" << memoryInfoBriefly_
       << ", networkInfo=" << networkInfo_
       << ", miscInfo=" << miscInfo_
       << ", diskUsageInfo=" << diskUsageInfo_
       << ", psTop10CpuUsage=";
    for (auto usage : psTop10CpuUsage_)
    {
        os << usage << std::endl;
    }
    os << ", psTop10MemoryUsage=";
    for (auto usage : psTop10MemoryUsage_)
    {
        os << usage << std::endl;
    }
    os << "nvidiaSmiGpuInfo=" << nvidiaSmiGpuInfo_;
    os << "infiniBandStatInfo=" << infiniBandStatInfo_;
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
    const CommandOutputString& psTop10CpuUsageStrs = Environment::instance().getShellCmdOutput(ShellCommandType::PsTop10CpuUsage);
    ShellCommandOutputParse::ParsePsTopnCpuUsageOutput(psTop10CpuUsageStrs, psTop10CpuUsage_);
    const CommandOutputString& psTop10MemoryUsageStrs = Environment::instance().getShellCmdOutput(ShellCommandType::PsTop10MemoryUsage);
    ShellCommandOutputParse::ParsePsTopnMemoryUsageOutput(psTop10MemoryUsageStrs, psTop10MemoryUsage_);

    const CommandOutputString& outputNvidiaSmiGpuInfo = Environment::instance().getShellCmdOutput(ShellCommandType::NvidiaSmiGpu);
    if (!outputNvidiaSmiGpuInfo.empty())
    {
        nvidiaSmiGpuInfo_.setCommand(ShellCommandType::NvidiaSmiGpu);
    }
    else
    {
        nvidiaSmiGpuInfo_.setCommand(ShellCommandType::InvalidType);
    }
    nvidiaSmiGpuInfo_.setCommandOutputString(outputNvidiaSmiGpuInfo);

    const CommandOutputString& outputInfiniBandStatInfo = Environment::instance().getShellCmdOutput(ShellCommandType::InfiniBandStat);
    if (!outputInfiniBandStatInfo.empty())
    {
        infiniBandStatInfo_.setCommand(ShellCommandType::InfiniBandStat);
    }
    else
    {
        infiniBandStatInfo_.setCommand(ShellCommandType::InvalidType);
    }
    infiniBandStatInfo_.setCommandOutputString(outputInfiniBandStatInfo);
}

}
