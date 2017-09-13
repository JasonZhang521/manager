#ifndef _ENVIRONMENT_CPUINFOBRIEFLY_H_
#define _ENVIRONMENT_CPUINFOBRIEFLY_H_
#include "Component.h"
#include "Macro.h"
#include <string>
#include <ostream>

namespace Serialize {
class WriteBuffer;
class ReadBuffer;
}

namespace Environment {
class CpuInfoBriefly
{
    uint16_t numOfCpu_;
    std::string modelName_;
    std::string frequency_;
    int usage_;
    int temprature_;
public:
    CpuInfoBriefly();
    CpuInfoBriefly(const CpuInfoBriefly& info);
    CpuInfoBriefly& operator =(const CpuInfoBriefly& info);
    inline void setNumOfCpu(uint16_t num) {numOfCpu_ = num;}
    inline uint16_t getNumOfCpu() const {return numOfCpu_;}
    inline void setModelName(const std::string& modelName) {modelName_ = modelName;}
    inline const std::string& getModelName() const {return modelName_;}
    inline void setFrequency(const std::string& frequency) {frequency_ = frequency;}
    inline const std::string& getFrequency() const {return frequency_;}
    inline void setUsage(int usage) {usage_ = usage;}
    inline int getUsage() const {return usage_;}

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);

    std::ostream& operator <<(std::ostream& os) const;
    bool operator ==(const CpuInfoBriefly& info) const;

    void update();
private:
    void updateCpuInfoBriefly();
    void updateCpuTemprature();
    void updateCpuTempratureFromProc();
    void updateCpuTempratureFromThermal();
    void updateCpuTempratureFromHwmon();
    void updateCpuTempratureFromVirtualHwmon();
    void updateCpuTemprature1(const std::string& tempFile);

public:
     GETCLASSNAME(CpuInfoBriefly)
};
}

inline std::ostream& operator <<(std::ostream& os, const Environment::CpuInfoBriefly& info)
{
    return info.operator <<(os);
}
#endif // _ENVIRONMENT_CPUINFOBRIEFLY_H_
