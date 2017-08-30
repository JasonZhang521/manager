#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QSplashScreen>
#include "loginpageii.h"
#include "ui_loginpageii.h"
#include "flowlayout.h"
#include "servercreationwindow.h"
#include "simplecrypt.h"
#include "clientworker.h"
#include "contactpage.h"
#include <QGraphicsDropShadowEffect>

LoginPageII::LoginPageII(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPageII)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //add shadows
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
    ui->widget->setGraphicsEffect(effect);

    m_setting = new QSettings("servers.ini",QSettings::IniFormat);//initilizing qsettings
    flowLayout=new FlowLayout; //create layout
    ui->scrollArea->setLayout(flowLayout); //set layout

    updateServerWidges();//

    //setup company information
    QCoreApplication::setOrganizationName("HzwTech");
    QCoreApplication::setOrganizationDomain("hzwtech.com");
    QCoreApplication::setApplicationName("HusterM");

    //set closes event
    connect(this,SIGNAL(closedWindow()),qApp,SLOT(quit()));
    //create  qsettings
    settings = new QSettings(this);
    //mask passwd input
    ui->lineEdit_login_password->setEchoMode(QLineEdit::Password);
    //set tab order
    this->setTabOrder(ui->comboBox_username,ui->lineEdit_login_password);
    this->setTabOrder(ui->lineEdit_login_password,ui->comboBox_server);
    this->setTabOrder(ui->comboBox_server,ui->pushButton_login_signin);

    //    this->setAttribute(Qt::WA_TranslucentBackground);
    //make login list
    processLoginCache();
    //set default ssh session info
    configure.port = 22;
    configure.verbosity = SSH_LOG_PROTOCOL;
    configure.unknownHostContinue = true;




    w = new MainWindow;
    w->show();

}

LoginPageII::~LoginPageII()
{
    delete ui;
}

//process login setting file
void LoginPageII::processLoginCache(){
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
bool LoginPageII::verifyUser(){
    return isValideUser;
}

//click login button
void LoginPageII::on_pushButton_login_signin_clicked()
{
    processloggingIn();
}

//click return key on passwd lineediter
void LoginPageII::on_lineEdit_login_password_returnPressed()
{
    processloggingIn();
}

//auto fill password if auto login selected
void LoginPageII::on_comboBox_username_activated(const QString &arg1)
{
    //identify if auto saving is checked
    if(ui->checkBox_autologin->isChecked()){
        //auto fill password
        ui->lineEdit_login_password->setText(settings->value("users/"+arg1).toString());
    }

}

//clear history logging info
void LoginPageII::on_pushButton_login_clear_clicked()
{
    settings->remove("users");
    settings->remove("servers");
    processLoginCache();
}

//identify if user validation passed
void LoginPageII::isValid(bool isValideUser){
    this->isValideUser=isValideUser;//reset identification
}

void LoginPageII::addServer_buttonClicked()
{


    ServerCreationWindow *w = new ServerCreationWindow;
    w->show();
    connect(w,SIGNAL(finished()),this,SLOT(processAddServerFinishEvent()));

}
void LoginPageII::runValidation(){
    this->hide();//hide login window
    QPixmap pixmap(":/Resources/loadbg.png");
    QSplashScreen splash(pixmap);


    splash.show();
    splash.showMessage("验证用户中... ");
    qApp->processEvents();

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

        connect(w,SIGNAL(changeUserSignal()),this,SLOT(showLoginPage()));
        //show splash screen at right place

        splash.showMessage("建立连接。正在初始化界面...");

        qApp->processEvents();

        w->setupSessionConfigure(configure);
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
void LoginPageII::changeUserSlot(){
    this->show();//show loginpage
    //open button
    ui->pushButton_login_signin->setText("登录");
    ui->pushButton_login_signin->setEnabled(true);
}
void LoginPageII::closeEvent (QCloseEvent *event)
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
void LoginPageII::showLoginPage(){
    this->show();
    //open button
    ui->pushButton_login_signin->setText("登录");
    ui->pushButton_login_signin->setEnabled(true);
}

void LoginPageII::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void LoginPageII::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void LoginPageII::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void LoginPageII::on_pushButton_login_exit_clicked()
{
    qApp->quit();
}

void LoginPageII::processAddServerFinishEvent()
{
    updateServerWidges();

}

void LoginPageII::updateServerWidges()
{
    clearWidgets(flowLayout);
    QPushButton* m_button = new QPushButton;//create button
    //    m_button->resize(80,80);
    m_button->setFixedSize(QSize(100,80));
    m_button->setText("+");
    m_button->setStyleSheet("background-color: blue;");//set button for add
    connect(m_button,SIGNAL(clicked()),this,SLOT(addServer_buttonClicked()));//connect add button signal to slot
    flowLayout->addWidget(m_button);//add to layout

    QStringList groups = m_setting->childGroups();
    foreach (QString each, groups) {qDebug()<<each;
        QPushButton* m_button = new QPushButton;
        m_button->setFixedSize(QSize(100,80));
        m_button->setStyleSheet("color: rgb(255, 255, 255);"
                                "background-color: blue;");
        m_button->setText(each);
        connect(m_button,SIGNAL(clicked()),this,SLOT(processConnectEvent()));


        flowLayout->addWidget(m_button);
    }
}

void LoginPageII::clearWidgets(QLayout * layout) {
    if (! layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}

void LoginPageII::processConnectEvent()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton) // this is the type we expect
    {
        QString buttonText = pButton->text();
        qDebug()<<buttonText;
        //fill login infos
        SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
        crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
        crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data


        m_setting->beginGroup(buttonText);

        QString user = m_setting->value("username").toString();//get username
        QString  password = crypto.decryptToString(m_setting->value("password").toString());//get passwd
        QString  hostname = m_setting->value("hostname").toString();//get hostname
        m_setting->endGroup();
        //show up
        ui->comboBox_username->setCurrentText(user);
        ui->lineEdit_login_password->setText(password);
        ui->comboBox_server->setCurrentText(hostname);

        configure.user = user.toStdString();
        configure.password =password.toStdString();
        configure.host = hostname.toStdString();

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
}
//run login logic
void LoginPageII::processloggingIn()
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


void LoginPageII::on_pushButton_clicked()
{
    ContactPage* c = new ContactPage;
    c->show();
}
