#ifndef SHELLWORKER_H
#define SHELLWORKER_H

#include <QObject>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <QObject>
using namespace SshWrapper;//set namespace
class ShellWorker : public QObject
{
    Q_OBJECT
public:
     ShellWorker(QObject *parent,SshConfigure configure);
     ~ShellWorker();

signals:
     //cpu
     void cpuFinished(QString str);
     //ram
     void ramFinished(QString str);
     //disk
     void diskFinished(QString str);
     //date
     void dateFinished(QString str);
     //uptime
     void uptimeFinished(QString str);
     //nodes
     void nodesFinished(QString str);
     //jobs by qsub
     void jobsQSubFinished(QStringList l1,QStringList l2);
     //jobs by showjobs
     void jobsShowjobsFinished(QStringList l1,QStringList l2);
     //declare finish signal
     void finished();

     void connectionFailedSignal();
     void connectionSuccessSignal();

public slots:
     void process();
private slots:
     void update();
     void Delay(int time);
private:
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;
    std::string outputString;//declare outputString

    bool isConnectionFailed = false;

    void getCPU();
    //ram
    void getRAM();

    //disk
    void getDISK();

    //date
    void getDATE();

    //uptime
    void getUPTIME();

    //nodes
    void getNODES();

    //jobs by qsub
    void getJOBS1();

    //jobs by showjobs
    void getJOBS2();

public:
    bool canceled_flag = false;
};

#endif // SHELLWORKER_H
