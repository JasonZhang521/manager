#include "MauiConfigurationUpdateResponse.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace ConfigureMgtMessage {

MauiConfigurationUpdateResponse::MauiConfigurationUpdateResponse()
{

}

MauiConfigurationUpdateResponse::~MauiConfigurationUpdateResponse()
{

}

void MauiConfigurationUpdateResponse::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_ConfigureMgt));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ManuiConfigureMgtUpdateResponseMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
}

void MauiConfigurationUpdateResponse::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
}

IpcMessage::IpcConfigureMgtMessageType MauiConfigurationUpdateResponse::getConfigureMgtType() const
{
    return IpcMessage::ManuiConfigureMgtUpdateResponseMessage;
}

std::ostream& MauiConfigurationUpdateResponse::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ConfigureMgt)
       << ", clusterMgtType=" << IpcMessage::IpcConfigureMgtTypeToString(IpcMessage::ManuiConfigureMgtUpdateResponseMessage)
       << "]";
    return os;
}
}
