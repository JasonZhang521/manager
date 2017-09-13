#include "UiIpcConnectionReceiver.h"
#include "UiClientHandler.h"
#include "IIpcMessage.h"
#include "IIpcMessageQueue.h"
#include "IpcMessageType.h"
#include "ReadBuffer.h"
#include "Trace.h"

namespace UiClient {

UiIpcConnectionReceiver::UiIpcConnectionReceiver(std::shared_ptr<IUiClientHandler> uiClientHandler,
                                                 std::shared_ptr<IpcMessage::IIpcMessageQueue> ipcMessageReceiveQueue)
    :uiClientHandler_(uiClientHandler)
    ,ipcMessageReceiveQueue_(ipcMessageReceiveQueue)
{

}

UiIpcConnectionReceiver::~UiIpcConnectionReceiver()
{

}

void UiIpcConnectionReceiver::onConnect()
{
    TRACE_ENTER();
    uiClientHandler_->onStartup();
}

void UiIpcConnectionReceiver::onReceive(std::unique_ptr<IpcMessage::IIpcMessage> msg)
{
    TRACE_ENTER();
    if (!uiClientHandler_)
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
        handleMessage(std::move(msg));
        break;
    case IpcMessage::IpcMessage_IpcCommunication:
        TRACE_NOTICE("Unsupport message! message type = " << IpcMessage::IpcMessageTypeString(msg->getMessageType()));
        break;
    default:
        TRACE_ERROR("Unsupported message! message type = " << IpcMessage::IpcMessageTypeString(msg->getMessageType()));
        break;
    }
}

void UiIpcConnectionReceiver::onDisconnect()
{
    TRACE_ENTER();
    uiClientHandler_->onShutdown();
}

void UiIpcConnectionReceiver::handleMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg)
{
    ipcMessageReceiveQueue_->pushBack(std::move(msg));
}

}
