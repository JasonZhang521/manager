#include "MauiConfigurationUpdateRequest.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace ConfigureMgtMessage {

MauiConfigurationUpdateRequest::MauiConfigurationUpdateRequest()
    : updateType_(REPLACE_FILE)
{

}

MauiConfigurationUpdateRequest::~MauiConfigurationUpdateRequest()
{

}

void MauiConfigurationUpdateRequest::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_ConfigureMgt));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ManuiConfigureMgtUpdateRequestMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
    mauiConfig_.serialize(writeBuffer);
    writeBuffer.write(static_cast<uint8_t>(updateType_));
}

void MauiConfigurationUpdateRequest::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
    mauiConfig_.unserialize(readBuffer);
    readBuffer.read<uint8_t>(temp);
    updateType_ = static_cast<ConfigureUpdateType>(temp);
}

IpcMessage::IpcConfigureMgtMessageType MauiConfigurationUpdateRequest::getConfigureMgtType() const
{
    return IpcMessage::ManuiConfigureMgtUpdateRequestMessage;
}

std::ostream& MauiConfigurationUpdateRequest::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ConfigureMgt)
       << ", clusterMgtType=" << IpcMessage::IpcConfigureMgtTypeToString(IpcMessage::ManuiConfigureMgtUpdateRequestMessage)
       << ", mauiConfig=" << mauiConfig_
       << "]";
    return os;
}

void MauiConfigurationUpdateRequest::setMauiConfig(const ConfigureManagement::MauiConfig& config)
{
   mauiConfig_ = config;
}

const ConfigureManagement::MauiConfig& MauiConfigurationUpdateRequest::getMauiConfig() const
{
    return mauiConfig_;
}

}
