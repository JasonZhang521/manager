#ifndef FORMFORTEST_H
#define FORMFORTEST_H

#include <QWidget>

#include "libssh/libssh.h"
#include <libssh/sftp.h>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <SftpDirAttribute.h>
using namespace SshWrapper;
namespace Ui {
class FormForTest;
}

class FormForTest : public QWidget
{
    Q_OBJECT

public:
    explicit FormForTest(QWidget *parent = 0);
    ~FormForTest();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FormForTest *ui;
    std::string user, password, hostname;
    SshConfigure m_configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;
    SftpDirAttributes attrs;

};

#endif // FORMFORTEST_H
