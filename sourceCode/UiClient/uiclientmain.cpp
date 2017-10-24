#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>
int main(int argc, char**argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    UiClient::UiClientProcess process;//tcp/ip client
    process.start();//运行client线程
    while (true) {
        while (process.messageReceived())
        {
            //输出消息内容，这里如果要获取消息对象里的数据，需要转换为相对应的消息类型
            std::unique_ptr<IpcMessage::IIpcMessage> msg = std::move(process.getOneMessage());
            std::cout << "-----------------------" << std::endl;
            std::cout << *msg << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
        //主动发送request
      //  System::Sleep(50000);
      //  std::unique_ptr<IpcMessage::IIpcMessage>
      //          controlNodeBrieflyInfoRequest(new SystemMonitorMessage::ControlNodeBrieflyInfoRequest);
      //  process.sendMessage(std::move(controlNodeBrieflyInfoRequest));
      //  System::Sleep(1000);
    }
    return 0;
}
