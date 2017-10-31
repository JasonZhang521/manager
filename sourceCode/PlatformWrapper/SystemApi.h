#ifndef SYSTEMAPI_H
#define SYSTEMAPI_H

namespace PlatformWrapper {

class SystemApi
{
public:
    SystemApi();
    static int getPid();
};

}
#endif // SYSTEMAPI_H
