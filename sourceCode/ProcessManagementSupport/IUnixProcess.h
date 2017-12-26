#ifndef _PROCESSMANAGEMENTSUPPORT_ILINUXPROCESS_H_
#define _PROCESSMANAGEMENTSUPPORT_ILINUXPROCESS_H_
#include <string>
namespace ProcessManagementSupport
{

enum class LPStatus
{
    STARTING,
    RUNNING,
    STOPPING,
    STOPPED
};

class IUnixProcess
{
protected:
    LPStatus status_;
public:
    IUnixProcess();
    virtual ~IUnixProcess();
    virtual void startProcess() = 0;
    virtual void stopProcess() = 0;
    virtual LPStatus checkStatus() = 0;
};
}
#endif // _PROCESSMANAGEMENTSUPPORT_ILINUXPROCESS_H_
