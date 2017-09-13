#ifndef _ENVIRONMENT_CPUUSAGEDATATYPE_H_
#define _ENVIRONMENT_CPUUSAGEDATATYPE_H_
#include <stdint.h>
#include <vector>
#include <iostream>

namespace Environment {

enum CpuUsageType
{
    CPU_USER        = 0,
    CPU_NICE        = 1,
    CPU_SYS         = 2,
    CPU_IDLE        = 3,
    CPU_IOWAIT      = 4,
    CPU_IRQ         = 5,
    CPU_SOFTIRQ     = 6,
    CPU_STEALSTOLEN = 7,
    CPU_GUEST       = 8,
    CPU_USAGE_TYPE_NUMBER = 9
};

using CpuUsageRawData = std::vector<uint64_t>;
using CpuUsageRawDatas = std::vector<CpuUsageRawData>;

class CpuUsageEntry
{
    unsigned int total_;
    unsigned int user_;
    unsigned int nice_;
    unsigned int sys_;
    unsigned int idle_;
    unsigned int intr_;
    unsigned int totalTime_;
public:
    inline CpuUsageEntry() : total_(0), user_(0), nice_(0), sys_(0), idle_(0), intr_(0) {}
    inline unsigned int getTotalUsage() const {return total_;}
    inline void setTotalUsage(unsigned int total) {total_ = total;}
    inline unsigned int getUserUsage() const {return user_;}
    inline void setUserUsage(unsigned int user) {user_ = user;}
    inline unsigned int getNiceUsage() const {return nice_;}
    inline void setNiceUsage(unsigned int nice) {nice_ = nice;}
    inline unsigned int getSysUsage() const {return sys_;}
    inline void setSysUsage(unsigned int sys) {sys_ = sys;}
    inline unsigned int getIdleUsage() const {return idle_;}
    inline void setIdleUsage(unsigned int idle) {idle_ = idle;}
    inline unsigned int getIntrUsage() const {return intr_;}
    inline void setIntrUsage(unsigned int intr) {intr_ = intr;}
    inline unsigned int getTotalTime() const {return totalTime_;}
    inline void setTotalTime(unsigned int totalTime) {totalTime_ = totalTime;}
	inline std::ostream& operator<<(std::ostream& os) const
	{
	    os << "[total=" << total_ << ", user=" << user_ << ", nice=" << nice_ 
		   << ", sys="  << sys_   << ", idle=" << idle_ << ", intr=" << intr_
		   << ", totalTime=" << totalTime_ << "]";
		return os;
	}

public:
    static const CpuUsageEntry Null;
};

inline std::ostream& operator<< (std::ostream& os, const CpuUsageEntry& entry)
{
	return entry.operator<<(os);
}

using CpuUsageEntrys = std::vector<CpuUsageEntry>;
inline std::ostream& operator<< (std::ostream& os, const CpuUsageEntrys& entrys)
{
    int index = 0;
    for (CpuUsageEntrys::const_iterator it = entrys.cbegin(); it != entrys.cend(); ++it, ++index)
    {
        if (0 == index)
        {
            os << "[cpu:" << *it << "]";
        }
        else
        {
            os << ", [cpu" << index << ":" << *it << "]";
        }
    }
    return os;
}

}

#endif // _ENVIRONMENT_CPUUSAGEDATATYPE_H_
