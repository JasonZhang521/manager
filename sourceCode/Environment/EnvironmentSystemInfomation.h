#ifndef _ENVIRONMENT_ENVIRONMENTSYSTEMINFOMATION_H_
#define _ENVIRONMENT_ENVIRONMENTSYSTEMINFOMATION_H_

namespace Environment {

class CpuInfoBriefly;
class MemoryInfoBriefly;

class EnvironmentSystemInfomation
{
public:
    EnvironmentSystemInfomation();
    static void getCpuInfoBriefly(CpuInfoBriefly& cpuInfoBriefly);
    static void getMemoryInfoBriefly(MemoryInfoBriefly& memoryInfoBriefly);
};
}

#endif // ENVIRONMENTSYSTEMINFOMATION_H
