#ifndef _CONFIGURE_SYSTEMENVIRONMENTCONFIGURE_H_
#define _CONFIGURE_SYSTEMENVIRONMENTCONFIGURE_H_
#include <string>

class SystemEnvironmentConfigure
{
    std::string tempPath_;
public:
    SystemEnvironmentConfigure();
    const std::string& getTempPath();
    void setTempPath(const std::string& path);
};

#endif // _CONFIGURE_SYSTEMENVIRONMENTCONFIGURE_H_
