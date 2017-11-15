#include "ftpworker.h"
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <time.h>

#define UPDATE_INTERVAL 2500
Q_DECLARE_METATYPE(SftpDirAttributes)

FtpWorker::FtpWorker(QObject *parent,SshConfigure configure) : QObject(parent)
{

    qRegisterMetaType<SftpDirAttributes>("SftpDirAttributes");
    //create ssh client
    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startSftp();
    client->startShell();

    timer = new QTimer(this);


}

//deconstructor
FtpWorker::~FtpWorker(){
    client->shutdownShell();
    client->shutdownSftp();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

//process work here
void FtpWorker::process1(){
    emit finished();
}

//process download
void FtpWorker::processDownload(QString filePathRemote,QString filePathLocal){
    client->getFile(filePathRemote.toStdString(),filePathLocal.toStdString());
    emit finishDownload();
}
// process upload
void FtpWorker::processUpload(QString filePathLocal,QString filePathRemote){
    client->putFile(filePathLocal.toStdString(),filePathRemote.toStdString());
    emit finishUpload();
}

// list dir
void FtpWorker::processListDirect(QString filePathRemote,int i){
    int i_ = i;
    QList<QStringList> out;
    client->executeShellCommand("cd "+filePathRemote.toStdString()+" && ls -l -t",outputString);
    foreach(QString each,QString::fromStdString(outputString).split("\n"))
    {
       if(!each.isEmpty()&&!each.split(QRegExp("[\\s]+")).isEmpty())
       {
           out.append(each.split(QRegExp("[\\s]+")));
       }
    }

    emit finishListDir(out,i_);
}

//rm file
void FtpWorker::processRMFile(QString filePathRemote){
    client->executeShellCommand("rm "+filePathRemote.toStdString(),outputString);
    emit finishRMFile();
}


//create new directory       ***********************  mkdir  *******************
void FtpWorker::processMkDir(QString filePathRemote,QString fileName){
    client->executeShellCommand("cd "+filePathRemote.toStdString()+" && mkdir "+fileName.toStdString(),outputString);
    emit finishMkDir();

}

//create new file            ***********************  touch  *******************
void FtpWorker::processMkFile(){

}
//rename file *******
void FtpWorker::processRenameFile(){

}
