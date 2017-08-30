#ifndef MONITORWORKER_H
#define MONITORWORKER_H

#include <QObject>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>

#include "monitorwindow.h"
#include "dataVisualPack/cpuusageinfo.h"
#include "dataVisualPack/datacontainer.h"

using namespace SshWrapper;//set namespace

class MonitorWorker : public QObject
{
    Q_OBJECT
public:
    MonitorWorker(QObject *parent, SshConfigure configure, QString hostname);
    ~MonitorWorker();

public:
    bool canceled_flag = false;
    bool started_flag = false;
    bool stoped_flag = false;

signals:
    void finished();

public slots:
    void process();
    void start();
private:
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;
    std::string outputString;//declare outputString

    MonitorWindow* w;
    QString m_host;
    int i =0;

    int n=10;
    DataContainer m_dataContainer;


enum PS_TYPE { GETPROCESSBYCPU,
               GETPROCESSBYMEM};

    void Delay(int time);

    void update(QString hostname);
    QList<QList<int> > getCpuOneTimeCount(QString input);
    QList<int> getRamUsage(QString input);
    QList<int> getDiskUsage(QString input);
    QList<QStringList> getProcesses(QString input, PS_TYPE type);
};

#endif // MONITORWORKER_H
