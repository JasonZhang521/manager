#include "IConfigureMgtMessage.h"

namespace ConfigureMgtMessage {

IConfigureMgtMessage::IConfigureMgtMessage()
{

}

IConfigureMgtMessage::~IConfigureMgtMessage()
{

}

IpcMessage::IpcMessageType IConfigureMgtMessage::getMessageType() const
{
    return IpcMessage::IpcMessage_ConfigureMgt;
}

}
