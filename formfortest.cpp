#include "formfortest.h"
#include "ui_formfortest.h"

#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>

FormForTest::FormForTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormForTest)
{
    ui->setupUi(this);
    //    Ui::FormForTest *ui;
    //    std::string user, password, hostname;
    //    SshConfigure m_configure;
    //    ssh_session session;
    //    SshShellChannel *channel;
    //    SshClientSession *clientSession;
    //    ISshClient *client;
    //    SftpDirAttributes attrs;
    m_configure.host="116.236.169.100";
    m_configure.port=22;
    m_configure.user="jincao";
    m_configure.password="111111";
    m_configure.unknownHostContinue=true;
    m_configure.verbosity=SSH_LOG_PROTOCOL;

    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->m_configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();
    client->startSftp();

//    client->getFile("WAVEDER","c:/new");
//    client->stopGetFile();

}

FormForTest::~FormForTest()
{
    delete ui;
}

void FormForTest::on_pushButton_clicked()
{
//    QThreadPool pool;
//    QtConcurrent::run(&pool, client->getFile("WAVEDER","c:/new"));
        client->getFile("WAVEDER","c:/new");
}

void FormForTest::on_pushButton_2_clicked()
{
    client->stopGetFile();
}
