#ifndef IIPCMESSAGEFACTORY_H
#define IIPCMESSAGEFACTORY_H
#include "IpcMessageType.h"
#include <stdint.h>

namespace IpcMessage {

class IIpcMessage;
using IpcMessageApplicationIntType = uint8_t;

class IIpcMessageFactory
{
public:
    IIpcMessageFactory();
    IIpcMessageFactory(IpcMessageType type);
    virtual ~IIpcMessageFactory();
    virtual IIpcMessage* createMessage(IpcMessageApplicationIntType type) const = 0;
    virtual IpcMessageType messageType();

private:
    IpcMessageType type_;
};

}

#endif // IIPCMESSAGEFACTORY_H
