#ifndef _IPCMESSAGE_IPCMESSAGETYPE_H_
#define _IPCMESSAGE_IPCMESSAGETYPE_H_
#include <string>
namespace IpcMessage {

enum IpcMessageType
{
    IpcMessage_None,
    IpcMessage_IpcCommunication,
    IpcMessage_SystemMonitor,
    IpcMessage_ConfigureMgt
};
std::string IpcMessageTypeString(IpcMessageType type);

enum SystemMonitorMessageType
{
    ComputerNodeInfoRequestMessage,  // request the system information
    ComputerNodeInfoReportMessage,  // system information message
    ControlNodeBrieflyInfoRequestMessage,
    ControlNodeBrieflyInfoResponseMessage
};
std::string SystemMonitorTypeString(SystemMonitorMessageType type);

enum IpcCommunicationMessageType
{
    IpcHeartbeatReportMessage,
    IpcAuthorizationRequstMessage,
    IpcAuthorizationResponseMessage
};
std::string IpcCommunicationTypeString(IpcCommunicationMessageType type);

enum IpcConfigureMgtMessageType
{
    ManuiConfigureMgtAcquireRequestMessage,
    ManuiConfigureMgtAcquireResponseMessage,
    ManuiConfigureMgtUpdateRequestMessage,
    ManuiConfigureMgtUpdateResponseMessage
};

std::string IpcConfigureMgtTypeToString(IpcConfigureMgtMessageType type);

}
#endif // _IPCMESSAGE_IPCMESSAGETYPE_H_
