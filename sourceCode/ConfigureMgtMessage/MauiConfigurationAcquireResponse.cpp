#include "MauiConfigurationAcquireResponse.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"

namespace ConfigureMgtMessage {

MauiConfigurationAcquireResponse::MauiConfigurationAcquireResponse()
{

}

MauiConfigurationAcquireResponse::~MauiConfigurationAcquireResponse()
{

}

void MauiConfigurationAcquireResponse::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::IpcMessageType::IpcMessage_ConfigureMgt));
    writeBuffer.write<uint8_t>(static_cast<uint8_t>(IpcMessage::ManuiConfigureMgtAcquireResponseMessage));
    IpcMessage::IIpcMessage::write(writeBuffer);
    mauiConfig_.serialize(writeBuffer);
}

void MauiConfigurationAcquireResponse::unserialize(Serialize::ReadBuffer& readBuffer)
{
    uint8_t temp = 0;
    readBuffer.read(temp);
    readBuffer.read(temp);
    IpcMessage::IIpcMessage::read(readBuffer);
    mauiConfig_.unserialize(readBuffer);
}

IpcMessage::IpcConfigureMgtMessageType MauiConfigurationAcquireResponse::getConfigureMgtType() const
{
    return IpcMessage::ManuiConfigureMgtAcquireResponseMessage;
}

std::ostream& MauiConfigurationAcquireResponse::operator<< (std::ostream& os) const
{
    os << "[";
    IpcMessage::IIpcMessage::print(os);
    os << ", ipcMessageType=" << IpcMessage::IpcMessageTypeString(IpcMessage::IpcMessage_ConfigureMgt)
       << ", clusterMgtType=" << IpcMessage::IpcConfigureMgtTypeToString(IpcMessage::ManuiConfigureMgtAcquireResponseMessage)
       << ", mauiConfig=" << mauiConfig_
       << "]";
    return os;
}

void MauiConfigurationAcquireResponse::setMauiConfig(const ConfigureManagement::MauiConfig& config)
{
   mauiConfig_ = config;
}

const ConfigureManagement::MauiConfig& MauiConfigurationAcquireResponse::getMauiConfig() const
{
    return mauiConfig_;
}

}
