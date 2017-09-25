#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>
int main(int argc, char**argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    UiClient::UiClientProcess process;
    process.setRemoteHost(std::string("116.236.169.100"));
    process.start();
    while (true) {
        while (process.messageReceived())
        {
            std::unique_ptr<IpcMessage::IIpcMessage> msg = std::move(process.getOneMessage());
//            IpcMessage::IIpcMessage* pMsg = msg.get(); //获取指针
            SystemMonitorMessage::ISystemMonitorMessage* systemMessage =
                        dynamic_cast<SystemMonitorMessage::ISystemMonitorMessage*>(msg.get());


            SystemMonitorMessage::ComputerNodeInfoReport* resp =
                    dynamic_cast<SystemMonitorMessage::ComputerNodeInfoReport *>(systemMessage);

             std::cout << "-----------------------" << std::endl;
//             std::cout << *msg << std::endl;
            std::cout << resp->getCpuUsageInfo()<<std::endl;
             std::cout << "-----------------------" << std::endl;

        }
//         System::Sleep(5000);
//         std::unique_ptr<IpcMessage::IIpcMessage>
//                 controlNodeBrieflyInfoRequest(new SystemMonitorMessage::ControlNodeBrieflyInfoRequest);
//         process.sendMessage(std::move(controlNodeBrieflyInfoRequest));
//         System::Sleep(1000);
    }
    return 0;
}
