#include "servercreationwindow.h"
#include "ui_servercreationwindow.h"
#include "simplecrypt.h"
#include <QMessageBox>

ServerCreationWindow::ServerCreationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerCreationWindow)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    this->setFixedSize(512,380);
    ui->treeWidget->header()->close();
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);

    m_setting = new QSettings("servers.ini",QSettings::IniFormat);//initilizing qsettings

}

ServerCreationWindow::~ServerCreationWindow()
{
    delete ui;
}

void ServerCreationWindow::on_pushButton_ok_clicked()
{
    //create crypter
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
    crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
    crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data
    //get all server infos
    QString name,hostname,username,password,notes,port;
    name=ui->lineEdit_name->text();//server name for identity
    username=ui->lineEdit_username->text();//user name for login
    password=ui->lineEdit_passwd->text();//passowrd for login
    hostname=ui->lineEdit_host->text();//hostname for login
    port=ui->lineEdit_host_port->text();
    notes=ui->textEdit_notes->toPlainText();//notes for description
    //store all infos
    if(!name.isEmpty()&&!username.isEmpty()&&!password.isEmpty()&&!hostname.isEmpty()&&!port.isEmpty())
    {
        m_setting->setValue(name+"/hostname",hostname);
        m_setting->setValue(name+"/port",port);
        m_setting->setValue(name+"/username",username);
        m_setting->setValue(name+"/password",crypto.encryptToString(password));
        m_setting->setValue(name+"/notes",notes);
    }

    else
    {
        QMessageBox msg;
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        msg.setText("信息不能为空");
        msg.exec();
        return;
    }
    emit finished();
    this->close();



}

void ServerCreationWindow::on_pushButton_cancel_clicked()
{
    this->close();
}
