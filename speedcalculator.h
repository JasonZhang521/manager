#ifndef SPEEDCALCULATOR_H
#define SPEEDCALCULATOR_H

#include <QObject>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <QTimer>
using namespace SshWrapper;//set namespace

class SpeedCalculator : public QObject
{
    Q_OBJECT
public:
     SpeedCalculator(QObject *parent,SshConfigure configure);
     ~SpeedCalculator();

signals:
     void finished();
     void getUploadSpeedSignal(int i,qint64 percentage);
     void getDownloadSpeedSignal(int i,qint64 percentage);

     void getCurrentFileSizeSignal(qint64 currentSize);
     void getFullFileSizeSignal(qint64 fullFileSize);


     void getCurrentFileSizeSignalUpload(qint64 currentSize);
     void getFullFileSizeSignalUpload(qint64 fullFileSize);

public slots:
     void process();
     void processUploadSpeed(QString filePathRemote, QString fileName, qint64 fullFileSize);
     void processDownloadSpeed(QString s1,QString s2,QString s3);
private slots:
     void update();
     void go();
     void Delay(int time);
private:
     SshConfigure configure;
     ssh_session session;
     SshShellChannel *channel;
     SshClientSession *clientSession;
     ISshClient *client;
     std::string outputString;

     qint64 preSize=0, currentSize=0;
     QTimer *timer;
     QString filePathRemote_;
     QString fileName_;
public:
     bool _isStoped = false;
};

#endif // SPEEDCALCULATOR_H
