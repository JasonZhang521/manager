#ifndef IPCWORKERII_H
#define IPCWORKERII_H

#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>


class IPCWorkerII
{
public:
    IPCWorkerII();
private:
    UiClient::UiClientProcess process;
};

#endif // IPCWORKERII_H
