#include "ISystemMonitorMessage.h"

namespace SystemMonitorMessage {

ISystemMonitorMessage::ISystemMonitorMessage()
{

}

ISystemMonitorMessage::~ISystemMonitorMessage()
{

}

IpcMessage::IpcMessageType ISystemMonitorMessage::getMessageType() const
{
    return IpcMessage::IpcMessageType::IpcMessage_SystemMonitor;
}

}
