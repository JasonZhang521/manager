#ifndef IIPCCONNECTIONSERVERSTRATEGY_H
#define IIPCCONNECTIONSERVERSTRATEGY_H
#include <memory>

namespace Ipc {
class IIpcConnectionAcceptor;

class IIpcConnectionServerStrategy
{
public:
    IIpcConnectionServerStrategy();
    ~IIpcConnectionServerStrategy();
    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void setIpcConnectionAcceptor(std::shared_ptr<IIpcConnectionAcceptor> acceptor) = 0;
};

}

#endif // IIPCCONNECTIONSERVERSTRATEGY_H
