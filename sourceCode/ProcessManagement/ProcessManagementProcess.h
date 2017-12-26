#ifndef PROCESSMANAGEMENTPROCESS_H
#define PROCESSMANAGEMENTPROCESS_H
#include <utility>
#include <string>
#include <vector>

namespace ProcessManagement {
class ProcessManagementProcess
{
    using ProcessParameter = std::pair<std::string, unsigned int>;
    using ProcessParameters = std::vector<ProcessParameter>;
    ProcessParameters parameters_;
public:
    ProcessManagementProcess();
    void addProcessParameter(const ProcessParameter& parameter);
    void process();
};
}

#endif // PROCESSMANAGEMENTPROCESS_H
