#include "ProcessManagementProcess.h"
#include "Generic.h"
#include <iostream>
int main(int argc, char *argv[])
{
    ProcessManagement::ProcessManagementProcess process;
    using ProcessParameter = std::pair<std::string, unsigned int>;
    const ProcessParameter DefaultPara({"", 0});
    ProcessParameter parameter = DefaultPara;
    for (int i = 1; i < argc; ++i)
    {
        if (i % 2 == 1)
        {
            parameter.first = argv[i];
        }
        else
        {
            parameter.second = lexical_cast<int>(std::string(argv[i]));
            if (parameter.first != std::string() && parameter.second > 0)
            {
               process.addProcessParameter(parameter);
               parameter = DefaultPara;
            }
        }
    }
    process.process();
    return 0;
}
