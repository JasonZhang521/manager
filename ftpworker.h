#ifndef FTPWORKER_H
#define FTPWORKER_H
//import ssh client libs
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <SftpDirAttribute.h>
#include <QObject>
#include <QTimer>
#include <QMetaType>
using namespace SshWrapper;//set namespace
class FtpWorker : public QObject
{
    Q_OBJECT

public:
    FtpWorker(QObject *parent,SshConfigure configure);//declare constructor
    ~FtpWorker();//deconstructor

signals:
    void finished();//declare finish signal
    void error(QString err);//declare err signal
    void finishDownload();//declare finishing download signal
    void finishUpload();//declare finishing upload singal
    void finishListDir(QList<QStringList> out,int i);
    void finishRMFile();
    void finishMkDir();
    void getUploadSpeedSignal(int);
    void findFileExistanceSignal(bool);
    void finishDownloadPauseSignal();
    void finishUploadPauseSignal();



public slots:
    void process1();//declare working process
public slots:
    void processDownload(QString filePathRemote, QString filePathLocal);//process download file
    void processUpload(QString filePathLocal, QString filePathRemote);//process upload file
    void processListDirect(QString filePathRemote, int i);
    void processRMFile(QString filePathRemote);
    void processMkDir(QString filePathRemote, QString fileName);
    void processMkFile();
    void processRenameFile();
    void pauseDownload();
    void pauseUpload();
private:
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;

    int preSize=0, currentSize=0;
    std::string outputString;
    QTimer *timer;
    QString filePathRemote_;
    QString fileName_;
public:
    ISshClient *client;


};

#endif // FTPWORKER_H
