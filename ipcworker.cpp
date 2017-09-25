#include "ipcworker.h"
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>

IPCWorker::IPCWorker(QObject *parent,std::string str) : QObject(parent)
{
//     hostName_ = QString::fromStdString(str);

   // QTimer *timer = new QTimer(this);
   // //   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   // //   timer->start(UPDATE_INTERAL);
   // timer->singleShot(1000,this,SLOT(update()));
//   setup(str);
}


IPCWorker::~IPCWorker()
{

}

void IPCWorker::setup(QString host)
{

  if(host.isEmpty()) return;
  process.setRemoteHost(host.toStdString());
  process.start();
}

void IPCWorker::getMessageOnceSlot()
{
  update();
}

void IPCWorker::processII(){


    qDebug()<<"process() executed";
    emit finished();
}

void IPCWorker::update(){
    qDebug()<<"updated";
        while (process.messageReceived())
        {
            std::unique_ptr<IpcMessage::IIpcMessage> msg = std::move(process.getOneMessage());
           IpcMessage::IIpcMessage* pMsg = msg.get(); //获取指针
           SystemMonitorMessage::ISystemMonitorMessage* systemMessage =
                       dynamic_cast<SystemMonitorMessage::ISystemMonitorMessage*>(msg.get());


           SystemMonitorMessage::ComputerNodeInfoReport* resp =
                   dynamic_cast<SystemMonitorMessage::ComputerNodeInfoReport *>(systemMessage);

             std::cout << "-----------------------lookhere" << std::endl;
             // std::cout << *msg << std::endl;
           std::cout << resp->getHostName()<<std::endl;
             std::cout << "-----------------------" << std::endl;

        }
         // System::Sleep(5000);
         // std::unique_ptr<IpcMessage::IIpcMessage>
         //         controlNodeBrieflyInfoRequest(new SystemMonitorMessage::ControlNodeBrieflyInfoRequest);
         // process.sendMessage(std::move(controlNodeBrieflyInfoRequest));
         // System::Sleep(1000);

}
