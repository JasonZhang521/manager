#include "MemoryInfoBriefly.h"
#include "MemoryUsageInfo.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include "Generic.h"
namespace Environment {
MemoryInfoBriefly::MemoryInfoBriefly()
{

}

MemoryInfoBriefly::MemoryInfoBriefly(const MemoryInfoBriefly& info)
    : memTotal_(info.memTotal_)
    , memFree_(info.memFree_)
{

}

MemoryInfoBriefly& MemoryInfoBriefly::operator =(const MemoryInfoBriefly& info)
{
    memTotal_ = info.memTotal_;
    memFree_ = info.memFree_;
    return *this;
}

void MemoryInfoBriefly::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(memTotal_);
    writeBuffer.write(memFree_);
}
void MemoryInfoBriefly::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read(memTotal_);
    readBuffer.read(memFree_);
}

std::ostream& MemoryInfoBriefly::operator <<(std::ostream& os) const
{
    os << "["
       << "memTotal=" << memTotal_ << " KB"
       << ", memFree=" << memFree_ << " KB"
       << "]";
    return os;
}

bool MemoryInfoBriefly::operator ==(const MemoryInfoBriefly& info) const
{
    return (memTotal_ == info.memTotal_ &&
            memFree_ == info.memFree_);
}

void MemoryInfoBriefly::update()
{
    updateMemUsageInfo();
}

void MemoryInfoBriefly::updateMemUsageInfo()
{
    MemoryUsageInfo memUsageInfo;
    memUsageInfo.update();
    const MemoryUsageInfoRawData& rawData = memUsageInfo.getMemoryUsageInfoRawData();
    memTotal_ = lexical_cast<uint64_t>(rawData[MEMTOTAL]);
    memFree_ = lexical_cast<uint64_t>(rawData[MEMFREE]) + lexical_cast<uint64_t>(rawData[CACHED]);
}
}
