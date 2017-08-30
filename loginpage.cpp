#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QSplashScreen>
#include "clientworker.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include "simplecrypt.h"
#include "contactpage.h"

LoginPage::LoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    //setup company information
    QCoreApplication::setOrganizationName("HzwTech");
    QCoreApplication::setOrganizationDomain("hzwtech.com");
    QCoreApplication::setApplicationName("HusterM");

    //set closes event
    connect(this,SIGNAL(closedWindow()),qApp,SLOT(quit()));
    //create  qsettings
    settings = new QSettings(this);
    server_settings = new QSettings("servers.ini", QSettings::IniFormat);
    //mask passwd input
    ui->lineEdit_login_password->setEchoMode(QLineEdit::Password);
    //set tab order
    this->setTabOrder(ui->comboBox_username,ui->lineEdit_login_password);
    this->setTabOrder(ui->lineEdit_login_password,ui->comboBox_server);
    this->setTabOrder(ui->comboBox_server,ui->pushButton_login_signin);
    //hide title bar
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //make login list
    processLoginCache();
    //set default ssh session info
    configure.port = 22;
    configure.verbosity = SSH_LOG_PROTOCOL;
    configure.unknownHostContinue = true;

    //    //set mask
    //    QPixmap bmap(":/Resources/temp/loginmask.png");
    //    ui->frame->setMask(bmap.mask());
    //    ui->frame->setAttribute(Qt::tr);

    //QGraphicsDropShadowEffect
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);

    QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect();
    effect2->setBlurRadius(10);

this->setStyleSheet("");
    ui->pushButton_login_signin->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;color: rgb(255, 255, 255);background-color: rgb(0, 170, 255);");

    ui->pushButton_login_exit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;color: rgb(255, 255, 255);background-color: rgb(0, 170, 255);");

    ui->pushButton_connect->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;color: rgb(255, 255, 255);background-color: rgb(0, 170, 255);");

    ui->frame->setStyleSheet("border:1px groove gray;border-radius:10px;padding:1px 1px;color: rgb(35, 202, 5);border-color: rgb(255, 255, 255);background-color: rgb(0, 0, 0);");
    ui->label_4->setGraphicsEffect(effect);
    ui->frame->setGraphicsEffect(effect2);
    ui->label->setStyleSheet("* {border : none}");
    ui->label_2->setStyleSheet("* {border : none}");
    ui->label_3->setStyleSheet("* {border : none}");
    ui->pushButton_server_setting->setStyleSheet("* {border : 2px groove gray;padding : 1px 1px}");
    //    ui->lineEdit_login_password->setStyleSheet("* {border-radius : none}");
    on_pushButton_server_setting_clicked();

}

//process login setting file
void LoginPage::processLoginCache(){
    //process setting file for saved user and server list
    //reset combox
    ui->comboBox_username->clear();
    ui->comboBox_server->clear();
    //retrieve userlist
    settings->beginGroup("users");
    QStringList users = settings->allKeys();
    settings->endGroup();
    //add userlist to combox
    ui->comboBox_username->addItems(users);
    //retrieve serverlist
    settings->beginGroup("servers");
    QStringList servers = settings->allKeys();
    settings->endGroup();
    //add serverlist to combox
    ui->comboBox_server->addItems(servers);

}

//verify valid user
bool LoginPage::verifyUser(){
    return isValideUser;
}

//deconstruct components
LoginPage::~LoginPage()
{
    delete ui;
}

//click login button
void LoginPage::on_pushButton_login_signin_clicked()
{   
    processloggingIn();
}

//click return key on passwd lineediter
void LoginPage::on_lineEdit_login_password_returnPressed()
{
    processloggingIn();
}

//click quit button
void LoginPage::on_pushButton_login_exit_clicked()
{
    qApp->quit();
}

//run login logic
void LoginPage::processloggingIn()
{
    //close button
    ui->pushButton_login_signin->setText("登录中...");
    ui->pushButton_login_signin->setEnabled(false);

    user = ui->comboBox_username->currentText().toStdString();//get username
    password = ui->lineEdit_login_password->text().toStdString();//get passwd
    hostname = ui->comboBox_server->currentText().toStdString();//get hostname
    //setup config
    configure.user = user;
    configure.password = password;
    configure.host = hostname;
    //this->hide();//hide login page

    //create thread
    QThread* thread = new QThread;
    ClientWorker* worker = new ClientWorker(0,configure);//create worker object
    worker->moveToThread(thread);//move worker to thread
    connect(worker,SIGNAL(isValid(bool)),this,SLOT(isValid(bool)));
    connect(worker, SIGNAL (finished()), this, SLOT (runValidation()));
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

//auto fill password if auto login selected
void LoginPage::on_comboBox_username_activated(const QString &arg1)
{
    //identify if auto saving is checked
    if(ui->checkBox_autologin->isChecked()){
        //auto fill password
        ui->lineEdit_login_password->setText(settings->value("users/"+arg1).toString());
    }

}

//clear history logging info
void LoginPage::on_pushButton_login_clear_clicked()
{
    settings->remove("users");
    settings->remove("servers");
    processLoginCache();
}

//identify if user validation passed
void LoginPage::isValid(bool isValideUser){
    this->isValideUser=isValideUser;//reset identification
}

void LoginPage::runValidation(){
    QPixmap pixmap(":/Resources/loading.jpg");
    QSplashScreen splash(pixmap);
    if(isValideUser){

        //identify if save password
        if(ui->checkBox_savePasswd->isChecked())
            //save user with password
            settings->setValue("users/"+ui->comboBox_username->currentText(),ui->lineEdit_login_password->text());
        else
            //save user withou password
            settings->setValue("users/"+ui->comboBox_username->currentText(),"");
        //identify if save server
        if(ui->checkBox_saveServer->isChecked())
            //save server with value 0
            settings->setValue("servers/"+ui->comboBox_server->currentText(),0);

        w = new MainWindow;
        connect(w,SIGNAL(changeUserSignal()),this,SLOT(showLoginPage()));
        //show splash screen at right place
        splash.show();
        qApp->processEvents();

        this->hide();//hide login window
        w->setupSessionConfigure(configure);
        w->show();//show main window
        splash.finish(w);
    }
    else{
        //show err message
        QMessageBox msgBox;
        msgBox.setText("登录失败");
        msgBox.exec();
        this->show();//show loginpage
        //open button
        ui->pushButton_login_signin->setText("登录");
        ui->pushButton_login_signin->setEnabled(true);
    }
}

void LoginPage::changeUserSlot(){
    this->show();//show loginpage
    //open button
    ui->pushButton_login_signin->setText("登录");
    ui->pushButton_login_signin->setEnabled(true);
}

void LoginPage::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "HusterM",
                                                                tr("确定退出吗?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        emit closedWindow();
        event->accept();
    }
}

void LoginPage::showLoginPage(){
    this->show();
    //open button
    ui->pushButton_login_signin->setText("登录");
    ui->pushButton_login_signin->setEnabled(true);
}

void LoginPage::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void LoginPage::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void LoginPage::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void LoginPage::on_pushButton_server_setting_clicked()
{
    s = new ServerWindow(this);
    connect(s,SIGNAL(connectSignal(QString)),this,SLOT(processConnectSignal(QString)));
    s->show();

}

void LoginPage::processConnectSignal(QString recieve){
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
    crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
    crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data
    QSettings *setting_ = new QSettings("servers.ini",QSettings::IniFormat);

    //close button
    ui->pushButton_login_signin->setText("登录中...");
    ui->pushButton_login_signin->setEnabled(false);
    setting_->beginGroup(recieve);
    //    qDebug()<<setting_->value("username").toString();


    QString user = setting_->value("username").toString();//get username
    QString  password = crypto.decryptToString(setting_->value("password").toString());//get passwd
    QString  hostname = setting_->value("hostname").toString();//get hostname
    setting_->endGroup();
    //show up
    ui->comboBox_username->setCurrentText(user);
    ui->lineEdit_login_password->setText(password);
    ui->comboBox_server->setCurrentText(hostname);
    //setup config
    configure.user = user.toStdString();
    configure.password = password.toStdString();
    configure.host = hostname.toStdString();
    //this->hide();//hide login page

    //create thread
    QThread* thread = new QThread;
    ClientWorker* worker = new ClientWorker(0,configure);//create worker object
    worker->moveToThread(thread);//move worker to thread
    connect(worker,SIGNAL(isValid(bool)),this,SLOT(isValid(bool)));
    connect(worker, SIGNAL (finished()), this, SLOT (runValidation()));
    connect(thread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void LoginPage::on_pushButton_connect_clicked()
{
    ContactPage *c = new ContactPage;
    c->show();
}
