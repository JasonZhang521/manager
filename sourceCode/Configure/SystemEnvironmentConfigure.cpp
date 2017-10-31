#include "SystemEnvironmentConfigure.h"
#include "Configure_Define.h"

SystemEnvironmentConfigure::SystemEnvironmentConfigure()
    : tempPath_(SystemTempDir)
{
}


const std::string& SystemEnvironmentConfigure::getTempPath()
{
    return tempPath_;
}

void SystemEnvironmentConfigure::setTempPath(const std::string& path)
{
    tempPath_ = path;
}
