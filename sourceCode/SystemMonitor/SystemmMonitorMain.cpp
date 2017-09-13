#include "SystemMonitorProcess.h"
int main(int argc, char**argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    SystemMonitor::SystemMonitorProcess process;
    process.process();
    return 0;
}
