#include "IIpcComunicationMessage.h"
namespace IpcMessage {
IIpcComunicationMessage::IIpcComunicationMessage()
{
}

IIpcComunicationMessage::~IIpcComunicationMessage()
{

}

IpcMessage::IpcMessageType IIpcComunicationMessage::getMessageType() const
{
    return IpcMessage::IpcMessageType::IpcMessage_IpcCommunication;
}

}
