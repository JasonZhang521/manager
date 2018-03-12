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
#include "serverwindow.h"
#include "simplecrypt.h"
#include "clientworker.h"
#include "contactpage.h"
#include "contactinfoform.h"
#include <QGraphicsDropShadowEffect>
#include "doubleclickedbutton.h"
#include "yunwei.h"
#include "productpage.h"

LoginPageII::LoginPageII(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPageII)
{
    ui->setupUi(this);
    //    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);// | Qt::WindowStaysOnTopHint
        this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);// | Qt::WindowStaysOnTopHint

    //add shadows
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
//    ui->widget->setGraphicsEffect(effect);

    m_setting = new QSettings("servers.ini",QSettings::IniFormat);//initilizing qsettings
    flowLayout=new FlowLayout; //create layout
    ui->scrollArea->setLayout(flowLayout); //set layout

    updateServerWidges();//

    //setup company information registor
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

    //make login list
    processLoginCache();
    //set default ssh session info
    configure.port = 22;
    configure.verbosity = SSH_LOG_PROTOCOL;
    configure.unknownHostContinue = true;

//    ui->frame->setStyleSheet("QPushButton { margin: 1px; border-color: #0c457e; border-style: outset;border-radius: 3px;border-width: 1px;color: black;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2198c0, stop: 1 #0d5ca6);}" "QPushButton:pressed {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0d5ca6, stop: 1 #2198c0);}");
        w = new MainWindow();
        w->move(0,0);
        w->setWindowState(Qt::WindowMaximized);
//        w->showFullScreen();
       w->show();
    ui->pushButton_4->setStyleSheet("*:hover {color : red}" "* {color : white}");
    ui->pushButton_3->setStyleSheet("*:hover {color : red}" "* {color : white}");
    ui->pushButton->setStyleSheet("*:hover {color : red}" "* {color : white}");
    ui->pushButton_login_exit->setStyleSheet("*:hover {color : red}" "* {color : white}");

    this->setMinimumSize(800,600);
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

        splash.showMessage("建立连接。正在初始化界面,请稍候等待...");

        qApp->processEvents();

        w->setupSessionConfigure(configure);
        // w->show();
        splash.finish(w);

    }
    else{
        //show err message
        QMessageBox msgBox;
        msgBox.setText("登录信息验证失败");
        msgBox.exec();
        this->show();//show loginpage
        //open button
        ui->pushButton_login_signin->setText("登录");
        ui->pushButton_login_signin->setEnabled(true);
        enableButtons();
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
    //    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "HusterM",
    //                                                                tr("确定退出吗?\n"),
    //                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
    //                                                                QMessageBox::Yes);
    //    if (resBtn != QMessageBox::Yes) {
    //        event->ignore();
    //    } else {
    //        emit closedWindow();
    //        event->accept();
    //    }
}
void LoginPageII::showLoginPage(){
    this->show();
    //open button
    ui->pushButton_login_signin->setText("登录");
    ui->pushButton_login_signin->setEnabled(true);
}

void LoginPageII::mousePressEvent(QMouseEvent* event)
{
    //    if(event->button() == Qt::LeftButton)
    //    {
    //        mMoving = true;
    //        mLastMousePosition = event->pos();
    //    }
}

void LoginPageII::mouseMoveEvent(QMouseEvent* event)
{
    //    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    //    {
    //        this->move(this->pos() + (event->pos() - mLastMousePosition));
    //    }
}

void LoginPageII::mouseReleaseEvent(QMouseEvent* event)
{
    //    if(event->button() == Qt::LeftButton)
    //    {
    //        mMoving = false;
    //    }
}

void LoginPageII::on_pushButton_login_exit_clicked()
{
    qApp->quit();
}

void LoginPageII::processAddServerFinishEvent()
{
    updateServerWidges();

}

void LoginPageII::disableButtons()
{
    ui->scrollArea->setEnabled(false);
}

void LoginPageII::enableButtons()
{
    ui->scrollArea->setEnabled(true);

}

void LoginPageII::updateServerWidges()
{
    clearWidgets(flowLayout);
    QPushButton* m_button = new QPushButton;//create button
    //    m_button->resize(80,80);
    m_button->setFixedSize(QSize(70,50));
    m_button->setText("添加");
    m_button->setStyleSheet("background-color: rgb(20,115,203,200); color: white;");//set button for add
    connect(m_button,SIGNAL(clicked()),this,SLOT(addServer_buttonClicked()));//connect add button signal to slot
    flowLayout->addWidget(m_button);//add to layout

    QStringList groups = m_setting->childGroups();
    foreach (QString each, groups) {
        DoubleClickedButton* m_button = new DoubleClickedButton;
        m_button->setFixedSize(QSize(70,50));
        m_button->setStyleSheet("color: rgb(255, 255, 255);"
                                "background-color: rgb(36,160,97,200);");
        m_button->setText(each);
        connect(m_button,SIGNAL(doubleClicked()),this,SLOT(processConnectEvent()));
        connect(m_button,SIGNAL(singleClicked()),this,SLOT(processButtonSelectionEvent()));


        flowLayout->addWidget(m_button);
    }
    QPushButton* m_button1 = new QPushButton;
    m_button1->setFixedSize(QSize(70,50));
    m_button1->setText("编辑");
    m_button1->setStyleSheet("background-color: rgb(20,115,203,200); color: white;");
    connect(m_button1,SIGNAL(clicked()),this,SLOT(processEditButtonClicked()));
    flowLayout->addWidget(m_button1);

}

void LoginPageII::processButtonSelectionEvent()
{


    DoubleClickedButton* pButton = qobject_cast<DoubleClickedButton*>(sender());
    QString temp_name;
    temp_name = pButton->text();


    //fill login infos
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
    crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
    crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data

    m_setting->beginGroup(pButton->text());

    QString user = m_setting->value("username").toString();//get username
    QString  password = crypto.decryptToString(m_setting->value("password").toString());//get passwd
    QString  hostname = m_setting->value("hostname").toString();//get hostname
    QString port = m_setting->value("port").toString();//get port number

    m_setting->endGroup();
    //show up
    ui->comboBox_username->setCurrentText(user);
    ui->lineEdit_login_password->setText(password);
    ui->comboBox_server->setCurrentText(hostname);

    configure.user = user.toStdString();
    configure.password =password.toStdString();
    configure.host = hostname.toStdString();
    configure.port = port.toInt();

    clearWidgets(flowLayout);
    QPushButton* m_button = new QPushButton;//create button
    //    m_button->resize(80,80);
    m_button->setFixedSize(QSize(70,50));
    m_button->setText("添加");
    m_button->setStyleSheet("background-color: rgb(20,115,203,200); color: white;");//set button for add
    connect(m_button,SIGNAL(clicked()),this,SLOT(addServer_buttonClicked()));//connect add button signal to slot
    flowLayout->addWidget(m_button);//add to layout

    QStringList groups = m_setting->childGroups();
    foreach (QString each, groups) {
        DoubleClickedButton* m_button = new DoubleClickedButton;
        m_button->setFixedSize(QSize(70,50));
        m_button->setStyleSheet("color: rgb(255, 255, 255);"
                                "background-color: rgb(36,160,97,200);");
        m_button->setText(each);
        if(each.compare(temp_name)==0)
        {
            m_button->setCheckable(true);
            m_button->setChecked(true);
        }
        connect(m_button,SIGNAL(doubleClicked()),this,SLOT(processConnectEvent()));
        connect(m_button,SIGNAL(singleClicked()),this,SLOT(processButtonSelectionEvent()));


        flowLayout->addWidget(m_button);
    }
    QPushButton* m_button1 = new QPushButton;
    m_button1->setFixedSize(QSize(70,50));
    m_button1->setText("编辑");
    m_button1->setStyleSheet("background-color: rgb(20,115,203,200); color: white;");
    connect(m_button1,SIGNAL(clicked()),this,SLOT(processEditButtonClicked()));
    flowLayout->addWidget(m_button1);



}

void LoginPageII::processEditButtonClicked()
{
    editAccountInfo();

}
void LoginPageII::testSingleClick()
{
    qDebug()<<"single clicked";
}

void LoginPageII::testDoubleClick()
{
    qDebug()<<"double clicked";
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

    //close button
    ui->pushButton_login_signin->setText("验证用户中...");
    ui->pushButton_login_signin->setEnabled(false);
    disableButtons();
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    if (pButton)
    {
        QString buttonText = pButton->text();

        //fill login infos
        SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
        crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
        crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data

        m_setting->beginGroup(buttonText);

        QString user = m_setting->value("username").toString();//get username
        QString  password = crypto.decryptToString(m_setting->value("password").toString());//get passwd
        QString  hostname = m_setting->value("hostname").toString();//get hostname
        QString port = m_setting->value("port").toString();//get port number

        m_setting->endGroup();
        //show up
        ui->comboBox_username->setCurrentText(user);
        ui->lineEdit_login_password->setText(password);
        ui->comboBox_server->setCurrentText(hostname);

        configure.user = user.toStdString();
        configure.password =password.toStdString();
        configure.host = hostname.toStdString();
        configure.port = port.toInt();

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
    ui->pushButton_login_signin->setText("验证用户中...");
    ui->pushButton_login_signin->setEnabled(false);

    user = ui->comboBox_username->currentText().toStdString();//get username
    password = ui->lineEdit_login_password->text().toStdString();//get passwd
    hostname = ui->comboBox_server->currentText().toStdString();//get hostname
    //setup config
    configure.user = user;
    configure.password = password;
    configure.host = hostname;
    configure.port = 22;
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
    ContactInfoForm *c = new ContactInfoForm;
    c->show();
}

void LoginPageII::on_scrollArea_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu;
    menu->addAction(QString(tr("编辑")),this,SLOT(editAccountInfo()));
    menu->exec(QCursor::pos());
}

void LoginPageII::editAccountInfo()
{//computer , i want you to invoke that server window and add edit functionality.

    ServerWindow * server_window = new ServerWindow;
    server_window->show();
    connect(server_window,SIGNAL(updateLoginServerWidgetSignal()),this,SLOT(updateServerWidges()));

}

void LoginPageII::on_pushButton_3_clicked()
{
    YunWei * y = new YunWei(this);
    y->show();
}

void LoginPageII::on_pushButton_4_clicked()
{
    ProductPage *p = new ProductPage;
    p->show();

}

void LoginPageII::setPosition()
{
    //    int outer_length = this->width();
    //    int outer_height = this->height();
    //    int inner_length = ui->widget->width();
    //    int inner_height = ui->widget->height();
    //    int pos_x = (outer_length-inner_length)/2;
    //    int pos_y = (outer_height-inner_height)/2;
    //    ui->widget->set

}
