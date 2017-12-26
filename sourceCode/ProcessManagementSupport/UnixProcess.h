#ifndef _PROCESSMANAGEMENTSUPPORT_LINUXPROCESS_H_
#define _PROCESSMANAGEMENTSUPPORT_LINUXPROCESS_H_
#include "IUnixProcess.h"
#include "Component.h"
#include "Macro.h"

namespace ProcessManagementSupport
{

class UnixProcess : public IUnixProcess
{
    std::string executedBinaryPath_;
    pid_t pid_;
public:
    UnixProcess(const std::string& executedBinaryPath);
    ~UnixProcess();
    virtual void startProcess();
    virtual void stopProcess();
    virtual LPStatus checkStatus();

public:
     GETCLASSNAME(IpcClient)
};

}
#endif // _PROCESSMANAGEMENTSUPPORT_LINUXPROCESS_H_
