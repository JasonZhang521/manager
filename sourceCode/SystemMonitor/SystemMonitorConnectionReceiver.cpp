#include "SystemMonitorConnectionReceiver.h"
#include "ISystemMonitorMessage.h"
#include "IpcMessageType.h"
#include "ReadBuffer.h"
#include "Trace.h"
#include <stdint.h>

namespace SystemMonitor {
SystemMonitorConnectionReceiver::SystemMonitorConnectionReceiver(std::shared_ptr<ISystemMonitorHandler> monitorHandler)
    :monitorHandler_(monitorHandler)
{
}

SystemMonitorConnectionReceiver::~SystemMonitorConnectionReceiver()
{

}

void SystemMonitorConnectionReceiver::onConnect()
{
    TRACE_ENTER();
    monitorHandler_->onStartup();
}

void SystemMonitorConnectionReceiver::onReceive(std::unique_ptr<IpcMessage::IIpcMessage> msg)
{
    TRACE_ENTER();
    if (!monitorHandler_)
    {
       TRACE_ERROR("Monitor Handler is not set!");
       throw std::runtime_error("Monitor Handler is not set!");
    }
    if (!msg)
    {
        TRACE_WARNING("Invalid message!");
        return;
    }

    IpcMessage::IpcMessageType type = msg->getMessageType();
    if (type == IpcMessage::IpcMessage_SystemMonitor)

    switch(type)
    {
    case IpcMessage::IpcMessage_SystemMonitor:
        handleSystemMonitorMessage(std::move(msg));
        break;
    case IpcMessage::IpcMessage_IpcCommunication:
        TRACE_NOTICE("Unsupport message! message type = " << IpcMessage::IpcMessageTypeString(msg->getMessageType()));
        break;
    default:
        TRACE_ERROR("Unsupported message! message type = " << IpcMessage::IpcMessageTypeString(msg->getMessageType()));
        break;
    }

}

void SystemMonitorConnectionReceiver::onDisconnect()
{
    TRACE_ENTER();
    monitorHandler_->onShutdown();
}

void SystemMonitorConnectionReceiver::handleSystemMonitorMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg)
{
    SystemMonitorMessage::ISystemMonitorMessage* message = dynamic_cast<SystemMonitorMessage::ISystemMonitorMessage*>(msg.get());
    if (message != nullptr)
    {
        IpcMessage::SystemMonitorMessageType systemMonitorType = message->getSystemMonitorType();
        switch (systemMonitorType)
        {
        case IpcMessage::SystemMonitorMessageType::ComputerNodeInfoRequestMessage:
            monitorHandler_->reportSystemInfo();
            break;
        default:
            TRACE_ERROR("Unsupported message! monitor type = " << IpcMessage::SystemMonitorTypeString(systemMonitorType));
            break;
        }
    }
    else
    {
        TRACE_ERROR("Unsupported message! message type = " << IpcMessage::IpcMessageTypeString(msg->getMessageType()));
    }
}

}
