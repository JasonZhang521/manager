#include "MauiConfigurationAcquireRequest.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace ConfigureMgtMessage {

MauiConfigurationAcquireRequest::MauiConfigurationAcquireRequest()
{

}

MauiConfigurationAcquireRequest::~MauiConfigurationAcquireRequest()
{

}

void MauiConfigurationAcquireRequest::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_ConfigureMgt));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ManuiConfigureMgtAcquireRequestMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
}

void MauiConfigurationAcquireRequest::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
}

IpcMessage::IpcConfigureMgtMessageType MauiConfigurationAcquireRequest::getConfigureMgtType() const
{
    return IpcMessage::ManuiConfigureMgtAcquireRequestMessage;
}

std::ostream& MauiConfigurationAcquireRequest::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ConfigureMgt)
       << ", clusterMgtType=" << IpcMessage::IpcConfigureMgtTypeToString(IpcMessage::ManuiConfigureMgtAcquireRequestMessage)
       << "]";
    return os;
}

}
