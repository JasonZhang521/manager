#ifndef IIPCSERVER_H
#define IIPCSERVER_H

namespace Ipc {
class IIpcServer
{
public:
    IIpcServer();
    ~IIpcServer();
    virtual void startup() = 0;
    virtual void shutdown() = 0;
};

}

#endif // IIPCSERVER_H
