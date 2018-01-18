#include "UiClientProcess.h"
#include "UiClientHandler.h"
#include "UiIpcConnectionReceiver.h"
#include "UiClientMessageSendTimer.h"
#include "SystemMonitorMessageFactory.h"
#include "IpcClient.h"
#include "IpcConnectionTcpClientStrategy.h"
#include "IpcClientCreator.h"
#include "IpcLayerMessageFactory.h"
#include "IpcThreadSafeMessageQueue.h"
#include "IIpcMessage.h"
#include "TcpClient.h"
#include "IpSocketEndpoint.h"
#include "EventTimer.h"
#include "LoopMain.h"
#include "NetworkEnv.h"
#include "IpAddress.h"
#include "Trace.h"
#include "Configure.h"
#include <memory>
#include <thread>

namespace UiClient {

UiClientProcess::UiClientProcess()
    : ipcMessageSendQueue_(new IpcMessage::IpcThreadSafeMessageQueue())
    , ipcMessageReceiveQueue_(new IpcMessage::IpcThreadSafeMessageQueue())
{

}

UiClientProcess::~UiClientProcess()
{
    Core::LoopMain::instance().loopStop();
    uiClientThread_->join();
}

void UiClientProcess::start()
{
     uiClientThread_ = std::unique_ptr<std::thread>(new std::thread(std::bind(&UiClientProcess::process, this)));
}
bool UiClientProcess::messageReceived()
{
    return !ipcMessageReceiveQueue_->isEmpty();
}

std::unique_ptr<IpcMessage::IIpcMessage> UiClientProcess::getOneMessage()
{
    if (!ipcMessageReceiveQueue_->isEmpty())
    {
        return ipcMessageReceiveQueue_->popFront();
    }
    else
    {
        return nullptr;
    }
}

void UiClientProcess::sendMessage(std::unique_ptr<IpcMessage::IIpcMessage> msg)
{
    ipcMessageSendQueue_->pushBack(std::move(msg));
}


void UiClientProcess::process()
{
    TRACE_NOTICE("Ui Client is starting!");
    // Local and remote endpoint.
    Network::IpSocketEndpoint localEndpoint("0.0.0.0:0");
    //Network::IpSocketEndpoint remoteEndpoint(std::string("127.0.0.1:23833"));
//    Network::IpSocketEndpoint remoteEndpoint(std::string("192.168.5.138:23833"));
//    Network::IpSocketEndpoint remoteEndpoint(std::string("116.236.169.100:23833"));
        Network::IpSocketEndpoint remoteEndpoint(address);

    // SystemMonitorHandler
    UiClientHandler* uiClientHandlerPtr = new UiClientHandler();
    std::shared_ptr<IUiClientHandler> uiClientHandler(uiClientHandlerPtr);

    // SystemMonitorConnectionReceiver
    std::shared_ptr<UiIpcConnectionReceiver>
            uiIpcConnectionReceiver(new UiIpcConnectionReceiver(uiClientHandler, ipcMessageReceiveQueue_));

    IpcMessageFactories factories;
    // System monitor factory
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new SystemMonitorMessage::SystemMonitorMessageFactory()));
    factories.push_back(std::shared_ptr<IpcMessage::IIpcMessageFactory>(new IpcMessage::IpcLayerMessageFactory()));

    Ipc::IIpcClient* ipcClientPtr = Ipc::IpcClientCreator::CreateWithTcpClientStrategy(localEndpoint, remoteEndpoint, uiIpcConnectionReceiver, factories);
    std::shared_ptr<Ipc::IIpcClient> ipcClient(ipcClientPtr);

    uiClientHandler->setIpcClient(ipcClient);
    uiClientHandler->startup();

    std::shared_ptr<UiClientMessageSendTimer>
            uiClientMessageSendTimer(new UiClientMessageSendTimer(ipcMessageSendQueue_, ipcClient));
    Core::LoopMain::instance().registerTimer(uiClientMessageSendTimer.get());
    // run
    Core::LoopMain::instance().loopStart();
    TRACE_NOTICE("Ui Client has ended!");
}

void UiClientProcess::setAddress(const std::string &value)
{
    address = value;
}
}
