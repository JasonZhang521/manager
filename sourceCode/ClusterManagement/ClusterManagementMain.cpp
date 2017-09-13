#include "ClusterManagementProcess.h"
int main(int argc, char**argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    ClusterManagement::ClusterManagementProcess process;
    process.process();
    return 0;
}
