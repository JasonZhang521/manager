#include "IIpcMessageFactory.h"
namespace IpcMessage {
IIpcMessageFactory::IIpcMessageFactory()
{

}

IIpcMessageFactory::IIpcMessageFactory(IpcMessageType type)
    :type_(type)
{

}

IIpcMessageFactory::~IIpcMessageFactory()
{

}

IpcMessageType IIpcMessageFactory::messageType()
{
    return type_;
}
}
