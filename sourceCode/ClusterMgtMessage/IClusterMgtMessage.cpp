#include "IClusterMgtMessage.h"
namespace ClusterMgtMessage {

IClusterMgtMessage::IClusterMgtMessage()
{

}
IClusterMgtMessage::~IClusterMgtMessage()
{

}

IpcMessage::IpcMessageType IClusterMgtMessage::getMessageType() const
{
    return IpcMessage::IpcMessage_ClusterMgt;
}

}
