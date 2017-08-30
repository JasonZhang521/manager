#include "mainwindow.h"
#include <QApplication>
#include "loginpage.h"
#include "serverwindow.h"
#include "servercreationwindow.h"
#include <QMessageBox>
#include "main.h"
#include "loginpageii.h"

int main(int argc, char *argv[])
{
    MyApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApplication a(argc, argv);
    LoginPageII l;
    l.show();


    try
    {
        a.exec();
    }
    catch (const std::bad_alloc &) {
        // clean up here, e.g. save the session
        // and close all config files.
        QMessageBox msg;
        msg.setText("Something goes wrong, contact developer for more help.");

        return 0; // exit the application
    }

}


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



