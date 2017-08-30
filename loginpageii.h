#ifndef LOGINPAGEII_H
#define LOGINPAGEII_H

#include <QWidget>
#include "flowlayout.h"
#include <QSettings>
#include <QDialog>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <mainwindow.h>
#include <serverwindow.h>
#include <QThread>
#include <QSplashScreen>
#include <QMouseEvent>
#include <QRegion>

namespace Ui {
class LoginPageII;
}

class LoginPageII : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPageII(QWidget *parent = 0);
    ~LoginPageII();



public slots:
    void processAddServerFinishEvent();
    void processConnectEvent();
    void changeUserSlot();
    void isValid(bool isValideUser);
    void runValidation();
    void showLoginPage();
protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void addServer_buttonClicked();
    void on_pushButton_login_exit_clicked();

    void on_pushButton_login_signin_clicked();

    void on_lineEdit_login_password_returnPressed();
    void on_comboBox_username_activated(const QString &arg1);
    void on_pushButton_login_clear_clicked();


    void on_pushButton_clicked();

private:
    Ui::LoginPageII *ui;
    //ssh related variables
    std::string user, password, hostname;
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;

    bool isValideUser = false;

    MainWindow *w;
     FlowLayout *flowLayout;
     QPoint mLastMousePosition;
     bool mMoving;

     QSettings *settings;//for login history cache
     QSettings* m_setting;//for server storation
     void updateServerWidges();
     void clearWidgets(QLayout *layout);
     void processLoginCache();
     bool verifyUser();
     void processloggingIn();


signals:
    void closedWindow();

};

#endif // LOGINPAGEII_H
