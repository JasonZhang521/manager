#include "ipcworkerii.h"

IPCWorkerII::IPCWorkerII()
{
    process.setRemoteHost(std::string("116.236.169.100"));
    process.start();

}
