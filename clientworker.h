#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
//import ssh client library
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
using namespace SshWrapper;//set namespace
class ClientWorker : public QObject
{
    Q_OBJECT
public:
     ClientWorker(QObject *parent, SshConfigure configure);//declare constructor
     ~ClientWorker();//declare deconstructor

signals:
    void finished();//declare finish signal
    void error(QString err);//declare err signal
    void isValid(bool isValidUser);

public slots:
    void process();//declare working process

private:
    //add private content
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;
    bool isValidUser;
};

#endif // CLIENTWORKER_H
