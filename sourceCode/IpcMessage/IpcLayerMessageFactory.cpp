#include "IpcLayerMessageFactory.h"
#include "IpcMessageType.h"
#include "IpcHeartbeatReport.h"
#include "IpcAuthorizationRequest.h"
#include "IpcAuthorizationResponse.h"
namespace IpcMessage {

IpcLayerMessageFactory::IpcLayerMessageFactory()
    : IIpcMessageFactory(IpcMessageType::IpcMessage_IpcCommunication)
{

}

IpcLayerMessageFactory::~IpcLayerMessageFactory()
{

}

IIpcMessage* IpcLayerMessageFactory::createMessage(IpcMessageApplicationIntType type) const
{
    if (type == IpcHeartbeatReportMessage)
    {
        return new IpcHeartbeatReport();
    }
    else if (type == IpcAuthorizationRequstMessage)
    {
        return new IpcAuthorizationRequest();
    }
    else if (type == IpcAuthorizationResponseMessage)
    {
        return new IpcAuthorizationResponse();
    }
    else
    {
        return nullptr;
    }
}

}
