#include "ClusterMgtClientsManagement.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "IIpcClient.h"
#include "IIpcServer.h"
#include "IIpcMessage.h"
#include "IpcMessageType.h"
#include "Trace.h"

namespace ClusterManagement {

ClusterMgtClientsManagment::ClusterMgtClientsManagment(ClientType clientType, std::shared_ptr<Ipc::IIpcServer> ipcServer)
    : clientType_(clientType)
    , ipcServer_(ipcServer)
{

}

ClusterMgtClientsManagment::~ClusterMgtClientsManagment()
{

}

void ClusterMgtClientsManagment::startup()
{
    TRACE_ENTER();
    ipcServer_->startup();
}

void ClusterMgtClientsManagment::shutdown()
{
    TRACE_ENTER();
    ipcServer_->shutdown();
}

void ClusterMgtClientsManagment::addAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint, std::shared_ptr<Ipc::IIpcClient> ipcClient)
{
    TRACE_DEBUG("Add client:" << remoteEndPoint);
    IpcClientsMap::iterator it= clients_.find(remoteEndPoint);
    if (it != clients_.end())
    {
        TRACE_WARNING("Ipc client :" << remoteEndPoint << " already exist!");
    }

    clients_[remoteEndPoint] = ipcClient;
}

void ClusterMgtClientsManagment::removeAcceptedIpcClient(const Network::IpSocketEndpoint& remoteEndPoint)
{
    TRACE_DEBUG("remove client:" << remoteEndPoint);
    IpcClientsMap::iterator it = clients_.find(remoteEndPoint);
    if (it != clients_.end())
    {
        clients_.erase(it);
    }
    else
    {
        TRACE_WARNING("Ipc client :" << remoteEndPoint << " already been removed!");
    }
}

void ClusterMgtClientsManagment::handleMessage(IpcMessage::IIpcMessage& msg, ClientType fromClientType, const Network::IpSocketEndpoint& remoteIpEndpoint)
{
	TRACE_DEBUG("msg=" << msg << ", fromClientType=" << static_cast<int>(fromClientType) << ", remoteIpEndpoint=" << remoteIpEndpoint);
    IpcMessage::IpcMessageType type = msg.getMessageType();
    if (type == IpcMessage::IpcMessageType::IpcMessage_SystemMonitor)
    {
        const SystemMonitorMessage::ISystemMonitorMessage* sMmsg = dynamic_cast<const SystemMonitorMessage::ISystemMonitorMessage*>(&msg);
        if (sMmsg && sMmsg->getSystemMonitorType() == IpcMessage::ComputerNodeInfoReportMessage)
        {
            if (fromClientType == clientType_)
            {
                return;
            }

            const std::string dest = msg.getDestnation().toString();
            TRACE_DEBUG("destination:" << dest);
            if (msg.getDestnation() == Network::IpSocketEndpoint::BroadCastAddress)
            {
                broadcastMsg(msg);
            }
            else if (msg.getDestnation().isValid())
            {
                IpcClientsMap::iterator it = clients_.find(dest);
                forwardIpcMessage(dest, msg);
            }
        }
        else
        {
            if (fromClientType != clientType_)
            {
                return;
            }

            handleClusterMgtMessage(msg, remoteIpEndpoint);
        }
    }
    else
    {
        if (fromClientType == clientType_)
        {
            return;
        }
        const std::string invalidDest("Invalid_IpAddress:0");
        const std::string dest = msg.getDestnation().toString();
        TRACE_DEBUG("destination:" << dest);
        if (dest == invalidDest)
        {
            broadcastMsg(msg);
        }
        else
        {
            IpcClientsMap::iterator it = clients_.find(dest);
            forwardIpcMessage(dest, msg);
        }
    }
}

void ClusterMgtClientsManagment::forwardIpcMessage(const Network::IpSocketEndpoint& remoteEndPoint, IpcMessage::IIpcMessage& msg)
{
    TRACE_DEBUG("Forward msg to:" << remoteEndPoint << ", msg = " << msg);
    IpcClientsMap::iterator it = clients_.find(remoteEndPoint);
    if (it != clients_.end())
    {
        std::shared_ptr<Ipc::IIpcClient>& ipcClient = it->second;
        ipcClient->send(msg);
    }
}

void ClusterMgtClientsManagment::broadcastMsg(IpcMessage::IIpcMessage& msg)
{
    TRACE_DEBUG("broad cast message to all client");
    for (IpcClientsMap::iterator it= clients_.begin(); it != clients_.end(); ++it)
    {
        std::shared_ptr<Ipc::IIpcClient>& ipcClient = it->second;
        ipcClient->send(msg);
    }
}

void ClusterMgtClientsManagment::handleClusterMgtMessage(const IpcMessage::IIpcMessage& msg, const Network::IpSocketEndpoint& remoteIpEndpoint)
{
	TRACE_DEBUG("msg=" << msg << ", remoteIpEndpoint=" << remoteIpEndpoint);
    const SystemMonitorMessage::ControlNodeBrieflyInfoRequest* request = dynamic_cast<const SystemMonitorMessage::ControlNodeBrieflyInfoRequest*>(&msg);
    if (request != nullptr)
    {
        SystemMonitorMessage::ControlNodeBrieflyInfoResponse response;
        Environment::SystemInfoBriefly info;
        info.update();
		TRACE_DEBUG(info);
        response.setSystemInfoBriefly(info);
        IpcClientsMap::iterator it = clients_.find(remoteIpEndpoint);
        if (it != clients_.end())
        {
            std::shared_ptr<Ipc::IIpcClient>& ipcClient = it->second;
            ipcClient->send(response);
        }
    }
}

}
