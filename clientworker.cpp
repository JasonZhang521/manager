#include "clientworker.h"

//construstor
ClientWorker::ClientWorker(QObject *parent,SshConfigure configure) : QObject(parent)
{
    //create ssh client
    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);


}
//deconstructor
ClientWorker::~ClientWorker(){
    client->shutdownShell();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

//process work here
void ClientWorker::process(){


    emit isValid(client->setup());
    emit finished();
}
