#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <mainwindow.h>
#include <serverwindow.h>
#include <QSettings>
#include <QThread>
#include <QSplashScreen>
#include <QMouseEvent>
#include <QRegion>


using namespace SshWrapper;
namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();

private slots:
    void on_pushButton_login_signin_clicked();
    void on_lineEdit_login_password_returnPressed();
    void on_pushButton_login_exit_clicked();
    void on_comboBox_username_activated(const QString &arg1);
    void on_pushButton_login_clear_clicked();
    void isValid(bool isValideUser);
    void runValidation();

    void on_pushButton_server_setting_clicked();

    void processConnectSignal(QString recieve);
    void on_pushButton_connect_clicked();

private:
    Ui::LoginPage *ui;
    std::string user, password, hostname;
    SshConfigure configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;

    QPixmap *pixmap;
    QSplashScreen *splash;//create splash screen

    MainWindow *w;
    ServerWindow *s;

    QPoint mLastMousePosition;
    bool mMoving;

    QSettings *settings;
    QSettings *server_settings;
    bool isValideUser = false;
    void processloggingIn();
    void processLoginCache();
    void closeEvent(QCloseEvent *event);
public:
    bool verifyUser();

public slots:
    void changeUserSlot();
    void showLoginPage();
signals:
    void closedWindow();
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // LOGINPAGE_H
