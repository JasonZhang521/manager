#ifndef IPCLAYERMESSAGEFACTORY_H
#define IPCLAYERMESSAGEFACTORY_H
#include "IIpcMessageFactory.h"

namespace IpcMessage {
class IpcLayerMessageFactory : public IIpcMessageFactory
{
public:
    IpcLayerMessageFactory();
    virtual ~IpcLayerMessageFactory();
    virtual IIpcMessage* createMessage(IpcMessageApplicationIntType type) const;
};

}

#endif // IPCLAYERMESSAGEFACTORY_H
