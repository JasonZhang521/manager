#include "mainwindow.h"
#include <QApplication>
#include "loginpage.h"
#include "serverwindow.h"
#include "servercreationwindow.h"
#include <QMessageBox>
#include "main.h"
#include "loginpageii.h"

//
#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>

//test
#include "ipcworkerii.h"

//
#include "m.h"
int main(int argc, char *argv[])
{
    MyApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApplication a(argc, argv);
    LoginPageII *l=new LoginPageII();
    l->show();
//    M* m;
//    m = new M();
//    m->show();
//    MainWindow* m;
//    m = new MainWindow();
//    m->show();

//    UiClient::UiClientProcess process;
//    process.start();
    return a.exec();
//    return 0;


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


// #include <libssh/libssh.h>
// #include <SshClient.h>
// #include <SshClientSession.h>
// #include <SshShellChannel.h>
// #include <SshConfigure.h>
//
// #include "manageworker.h"
// #include <QApplication>
//
// int main(int argc, char *argv[])
// {
//    QCoreApplication a(argc,argv);
//    SshConfigure config_;
//    config_.user="root";
//    config_.password="123581321";
//    config_.host="hpc2.hzwtech.com";
//    config_.port = 22;
//    config_.verbosity = SSH_LOG_PROTOCOL;
//    config_.unknownHostContinue = true;
//
//    ManageWorker *worker = new ManageWorker(0,config_);
//    // worker->getAllQueue();
//    worker->test();
//    return a.exec();
// }

//#include <QApplication>
//#include "contactinfoform.h"
//#include <QDebug>
//#include <thirdPartyLib/src/SmtpMime>
//#include "contactpage.h"
//#include "mainwindow.h"
//#include "loginpageii.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc,argv);
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//LoginPageII m;
//m.show();
//    return a.exec();


//}

//#include <QApplication>
//#include "UiClientProcess.h"
//#include "ControlNodeBrieflyInfoRequest.h"
//#include "ControlNodeBrieflyInfoResponse.h"
//#include "ComputerNodeInfoReport.h"
//#include "IIpcMessage.h"
//#include "Sleep.h"
//#include "Trace.h"
//#include <memory>
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc,argv);
//    UiClient::UiClientProcess process;
//    process.setRemoteHost(std::string("116.236.169.100"));
//    process.start();

//        while (process.messageReceived())
//        {
//            std::unique_ptr<IpcMessage::IIpcMessage> msg = std::move(process.getOneMessage());
//            IpcMessage::IIpcMessage* pMsg = msg.get(); //获取指针
//            SystemMonitorMessage::ISystemMonitorMessage* systemMessage =
//                    dynamic_cast<SystemMonitorMessage::ISystemMonitorMessage*>(msg.get());


//            SystemMonitorMessage::ComputerNodeInfoReport* resp =
//                    dynamic_cast<SystemMonitorMessage::ComputerNodeInfoReport *>(systemMessage);

//            std::cout << "-----------------------" << std::endl;
//            //             std::cout << *msg << std::endl;
//            std::cout << resp->getCpuUsageInfo()<<std::endl;
//            std::cout << "-----------------------" << std::endl;

//        }


//    return a.exec();
//}
