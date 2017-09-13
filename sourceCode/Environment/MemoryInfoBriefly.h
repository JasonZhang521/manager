#ifndef _ENVIRONMENT_MEMORYINFOBRIEFLY_H_
#define _ENVIRONMENT_MEMORYINFOBRIEFLY_H_
#include <string>
#include <ostream>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {
class MemoryInfoBriefly
{
    uint64_t memTotal_;
    uint64_t memFree_;
public:
    MemoryInfoBriefly();
    MemoryInfoBriefly(const MemoryInfoBriefly& info);
    MemoryInfoBriefly& operator =(const MemoryInfoBriefly& info);
    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const MemoryInfoBriefly& info) const;
    void update();

    inline uint64_t getMemTotal() const {return memTotal_;}
    inline void setMemTotal(uint64_t memTotal) {memTotal_ = memTotal;}
    inline uint64_t getMemFree() const {return memFree_;}
    inline void setMemFree(const uint64_t memFree) {memFree_ = memFree;}
private:
    void updateMemUsageInfo();
};
}

inline std::ostream& operator <<(std::ostream& os, const Environment::MemoryInfoBriefly& info)
{
    return info.operator <<(os);
}

#endif // _ENVIRONMENT_MEMORYUSAGEINFO_H_
