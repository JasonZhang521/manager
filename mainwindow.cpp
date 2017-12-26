#include "loginpageii.h"
#include "mainwindow.h"
#include <QProcess>
#include <QString>
#include <winsock2.h>
#include <Windows.h>
#include <QWindow>
#include <QLayout>
#include <QMessageBox>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>
#include <time.h>
#include <QScrollBar>
#include <QTreeWidget>

#include "monitorworker.h"
#include "timeuserselectiondialog.h"
#include <QDesktopWidget>

#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    qsrand(112233);

    model=new QDirModel;
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    ui.treeView->setModel(model);

    //    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::setActiveWindow(this);
    createCircleBar();
    QButtonGroup *group1=new QButtonGroup(ui.horizontalLayout_29);
    QButtonGroup *group2=new QButtonGroup(ui.horizontalLayout_40);
    group1->addButton(ui.radioButton_parameter_by_nodenum);
    group1->addButton(ui.radioButton_parameter_byNodeName);
    group2->addButton(ui.radioButton_openmpi);
    group2->addButton(ui.radioButton_mpich2);
    group2->addButton(ui.radioButton_othermpi);


    ui.tabWidget->setTabPosition(QTabWidget::West);
    this->setFocusPolicy( Qt::StrongFocus);

    setupStyleSheet();

    current_user_label.setText("当前用户: ");
    current_state_label.setText("  当前状态: ");

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    ui.toolBar->addAction(ui.action_connect);
    ui.toolBar->addSeparator();
    ui.toolBar->addAction(ui.action_disconnect);
    ui.toolBar->addAction(ui.action_changeUser);
    ui.toolBar->addSeparator();
    ui.toolBar->addWidget(spacerWidget);
    ui.toolBar->addWidget(&current_user_label);
    ui.toolBar->addWidget(&current_user_label_show);
    ui.toolBar->addWidget(&current_state_label);
    ui.toolBar->addWidget(&current_state_label_show);
    this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());


    highLighter = new Highlighter(ui.textBrowser_job_submit_show->document());
    highLighter2 = new Highlighter(ui.textBrowser_job_submit_show_2->document());
    setPlotStyle();

}

void MainWindow::setPlotBackground()
{
    QBrush backRole;
    backRole.setColor("black");
    backRole.setStyle(Qt::SolidPattern);
    ui.plot_cpuUsage->setBackground(backRole);
    ui.plot_cpuHistory->setBackground(backRole);
    ui.plot_ramUsage->setBackground(backRole);
    ui.plot_ramUsageHistory->setBackground(backRole);
}

void MainWindow::setCPUHistoryPlotStyle()
{

    x.append(0);
    y.append(0);

    QPen pen;
    pen.setColor(QColor(41,166,244));

    ui.plot_cpuHistory->addGraph();
    ui.plot_cpuHistory->graph(0)->setPen(pen);
    //    ui.plot_cpuHistory->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui.plot_cpuHistory->graph(0)->setData(x,y);
    ui.plot_cpuHistory->xAxis->setLabel("");
    ui.plot_cpuHistory->yAxis->setLabel("");
    ui.plot_cpuHistory->xAxis->setRange(-50,0);
    ui.plot_cpuHistory->yAxis->setRange(0,100);
    ui.plot_cpuHistory->replot();


}

void MainWindow::setRAMHistoryPlotStyle()
{
    x1.append(0);
    y1.append(0);

    QPen pen;
    pen.setColor(QColor(41,166,244));

    ui.plot_ramUsageHistory->addGraph();
    ui.plot_ramUsageHistory->graph(0)->setPen(pen);
    ui.plot_ramUsageHistory->graph(0)->setData(x,y);
    ui.plot_ramUsageHistory->xAxis->setLabel("");
    ui.plot_ramUsageHistory->yAxis->setLabel("");
    ui.plot_ramUsageHistory->xAxis->setRange(-50,0);
    ui.plot_ramUsageHistory->yAxis->setRange(0,100);
    ui.plot_ramUsageHistory->replot();
}

void MainWindow::setCpuPlotData(int input)
{
    QVector<QString> labels;
    ticks << 1;
    labels << "%";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui.plot_cpuUsage->xAxis->setTicker(textTicker);
    //set data
    regen = new QCPBars(ui.plot_cpuUsage->xAxis, ui.plot_cpuUsage->yAxis);
    regen->setAntialiased(false);
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));

    //set data
    regenData   << input;
    regen->setData(ticks, regenData);
}

void MainWindow::setCPUPlotCustomizeStyle()
{
    //custimize cpuusage plot
    ui.plot_cpuUsage->yAxis->setRange(0,100);
    ui.plot_cpuUsage->yAxis->setPadding(1); // a bit more space to the left border
    //    ui.plot_cpuUsage->yAxis->setLabel("");
    ui.plot_cpuUsage->yAxis->setBasePen(QPen(Qt::white));
    ui.plot_cpuUsage->yAxis->setTickPen(QPen(Qt::white));
    ui.plot_cpuUsage->yAxis->setSubTickPen(QPen(Qt::white));
    ui.plot_cpuUsage->yAxis->grid()->setSubGridVisible(false);
    ui.plot_cpuUsage->yAxis->setTickLabelColor(Qt::white);
    ui.plot_cpuUsage->yAxis->setLabelColor(Qt::white);
    ui.plot_cpuUsage->yAxis->setVisible(true);
    ui.plot_cpuUsage->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui.plot_cpuUsage->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // prepare x axis with  labels:

    ui.plot_cpuUsage->xAxis->setTickLabelRotation(60);
    ui.plot_cpuUsage->xAxis->setSubTicks(false);
    ui.plot_cpuUsage->xAxis->setTickLength(0,1);
    ui.plot_cpuUsage->xAxis->setRange(0.5, 1.5);
    ui.plot_cpuUsage->xAxis->setBasePen(QPen(Qt::white));
    ui.plot_cpuUsage->xAxis->setTickPen(QPen(Qt::white));
    ui.plot_cpuUsage->xAxis->grid()->setVisible(true);
    ui.plot_cpuUsage->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui.plot_cpuUsage->xAxis->setTickLabelColor(Qt::white);
    ui.plot_cpuUsage->xAxis->setLabelColor(Qt::white);
}

void MainWindow::setRamPlotCustomizeStyle()
{
    //custimize ram usage plot
    ui.plot_ramUsage->yAxis->setRange(0,100);
    ui.plot_ramUsage->yAxis->setPadding(1); // a bit more space to the left border
    //    ui.plot_ramUsage->yAxis->setLabel("cpu usage");
    ui.plot_ramUsage->yAxis->setBasePen(QPen(Qt::white));
    ui.plot_ramUsage->yAxis->setTickPen(QPen(Qt::white));
    ui.plot_ramUsage->yAxis->setSubTickPen(QPen(Qt::white));
    ui.plot_ramUsage->yAxis->grid()->setSubGridVisible(false);
    ui.plot_ramUsage->yAxis->setTickLabelColor(Qt::white);
    ui.plot_ramUsage->yAxis->setLabelColor(Qt::white);
    ui.plot_ramUsage->yAxis->setVisible(true);
    ui.plot_ramUsage->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui.plot_ramUsage->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));


    ui.plot_ramUsage->xAxis->setTickLabelRotation(60);
    ui.plot_ramUsage->xAxis->setSubTicks(false);
    ui.plot_ramUsage->xAxis->setTickLength(0,1);
    ui.plot_ramUsage->xAxis->setRange(0.5, 1.5);
    ui.plot_ramUsage->xAxis->setBasePen(QPen(Qt::white));
    ui.plot_ramUsage->xAxis->setTickPen(QPen(Qt::white));
    ui.plot_ramUsage->xAxis->grid()->setVisible(true);
    ui.plot_ramUsage->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui.plot_ramUsage->xAxis->setTickLabelColor(Qt::white);
    ui.plot_ramUsage->xAxis->setLabelColor(Qt::white);
}

void MainWindow::setRamPlotData(int input)
{
    int temp = input;
    // prepare x axis with  labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1;
    labels << "%";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui.plot_ramUsage->xAxis->setTicker(textTicker);

    rengen2 = new QCPBars(ui.plot_ramUsage->xAxis, ui.plot_ramUsage->yAxis);
    rengen2->setAntialiased(false);
    rengen2->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    rengen2->setBrush(QColor(0, 168, 140));

    //set data
    QVector<double> regen2Data;
    regen2Data   << 66;
    rengen2->setData(ticks, regen2Data);
}
void MainWindow::setPlotStyle()
{
    setPlotBackground();
    setCPUHistoryPlotStyle();

    setCPUPlotCustomizeStyle();
    setCpuPlotData(22);

    setRAMHistoryPlotStyle();
    setRamPlotCustomizeStyle();
    setRamPlotData(30);

}

void MainWindow::updateCPUTotal(int input)
{

    ticks.clear();
    QVector<QString> labels;
    ticks << 1;
    labels << "%";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui.plot_cpuUsage->xAxis->setTicker(textTicker);

    regenData.clear();
    qDebug()<<"@1";
    qDebug()<<input;
    regenData   << input;
    regen->setData(ticks, regenData);
    ui.plot_cpuUsage->replot();

}

void MainWindow::updateRamTotal(int input)
{
    // prepare x axis with  labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1;
    labels << "%";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui.plot_ramUsage->xAxis->setTicker(textTicker);

    //set data
    QVector<double> regen2Data;
    regen2Data << input;
    rengen2->setData(ticks, regen2Data);
    ui.plot_ramUsage->replot();

}

void MainWindow::updatePlotHeatBeat()
{


}

void MainWindow::setupStyleSheet()
{
    qApp->setStyleSheet("QMenuBar {background-color: #f0fff0;}"
                        "QTabBar::tab:selected {margin-left: -4px;margin-right: -4px;}"
                        "QTabBar::tab:selected {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(236, 255, 172), stop:1 #f0fff0);}"
                        "QTabBar::tab:selected {border-top-left-radius: 0px;border-bottom-left-radius: 0px;/*background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f0fff0, stop: 0.4 #f0fff0,stop: 0.5 #f0fff0, stop: 1.0 #f0fff0);*/}"
                        "QTabBar::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);border: 2px solid #C4C4C3;border-bottom-color: #C2C7CB;border-top-left-radius: 10px;border-bottom-left-radius: 10px;min-width: 18ex;}"
                        "QTabWidget::pane { border-top: 2px solid #C2C7CB;} "
                        "QTabBar::tab {padding-bottom: 10 px; background-color: #FFD39B/*rgba(211, 255, 211, 255)*/;} "
                        "QTabBar::tab:hover {background-color: rgb(28, 67, 255);}"
                        "QProgressBar {border: 0px solid grey; border-radius: 5px;}"
                        "QProgressBar::chunk {background-color: #05B8CC;width: 20px;margin: 0.5px;}"
                        "QScrollArea::verticalScrollBar {background-color: #ffd39b;alternate-background-color: #D5EAFF;}"
                        "QScrollArea::horizontalScrollBar {background-color: #ffd39b;alternate-background-color: #D5EAFF;}"
                        "QTreeWidget::verticalScrollBar {background-color: #ffd39b;alternate-background-color: #D5EAFF;}"
                        "QTreeWidget::horizontalScrollBar {background-color: #ffd39b;alternate-background-color: #D5EAFF;}"
                        "QMenuBar {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #98f898, stop:1 #f0fff0);}"
                        "QMenuBar::item {spacing: 3px; /* spacing between menu bar items */padding: 1px 4px;background: transparent;border-radius: 4px;}"
                        "QMenuBar::item:selected { /* when selected using mouse or keyboard */background: #f0fff0;}"
                        "QMenuBar::item:pressed {background: #888888;}"
                        "QMenu {background-color: white;margin: 2px; /* some spacing around the menu */}"
                        "QMenu::item {padding: 2px 25px 2px 20px;border: 1px solid transparent; /* reserve space for selection border */}"
                        "QMenu::item:selected {border-color: darkblue;background: rgba(100, 100, 100, 150);}"
                        "QMenu::icon:checked { /* appearance of a 'checked' icon */background: gray;border: 1px inset gray;position: absolute;top: 1px;right: 1px;bottom: 1px;left: 1px;}"
                        "QMenu::separator {height: 2px;background: lightblue;margin-left: 10px;margin-right: 5px;}"
                        "QMenu::indicator {width: 13px;height: 13px;}"
                        "QToolBar {background-color: #f0fff0}"
                        "QToolBar::item {spacing: 3px; /* spacing between menu bar items */padding: 1px 4px;background: transparent;border-radius: 4px;}"
                        "QToolBar::item:selected { /* when selected using mouse or keyboard */background: #f0fff0;}"
                        "QToolBar::item:pressed {background: #888888;}"

                        );
    ui.scrollArea->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                      "alternate-background-color: #D5EAFF;");
    ui.scrollArea_2->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                        "alternate-background-color: #D5EAFF;");
    ui.scrollArea_2->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                          "alternate-background-color: #D5EAFF;");
    ui.scrollArea_3->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                        "alternate-background-color: #D5EAFF;");
    ui.scrollArea_3->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                          "alternate-background-color: #D5EAFF;");
    ui.treeView->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                    "alternate-background-color: #D5EAFF;");
    ui.treeView->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                      "alternate-background-color: #D5EAFF;");
    ui.treeWidget->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                      "alternate-background-color: #D5EAFF;");
    ui.treeWidget->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                        "alternate-background-color: #D5EAFF;");
    ui.treeWidget_bottomMessage->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                    "alternate-background-color: #D5EAFF;");
    ui.treeWidget_bottomMessage->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                      "alternate-background-color: #D5EAFF;");
    ui.listWidget_control_nodes->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                    "alternate-background-color: #D5EAFF;");
    ui.listWidget_control_nodes->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                      "alternate-background-color: #D5EAFF;");
    ui.treeWidget_control_queue_view->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                         "alternate-background-color: #D5EAFF;");
    ui.treeWidget_control_queue_view->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                           "alternate-background-color: #D5EAFF;");
    ui.treeWidget_control_time_statics->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                           "alternate-background-color: #D5EAFF;");
    ui.treeWidget_control_time_statics->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                             "alternate-background-color: #D5EAFF;");
    ui.treeWidget_jobsubmitfile->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                    "alternate-background-color: #D5EAFF;");
    ui.treeWidget_jobsubmitfile->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                      "alternate-background-color: #D5EAFF;");
    ui.treeWidget_job_file->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                               "alternate-background-color: #D5EAFF;");
    ui.treeWidget_job_file->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                 "alternate-background-color: #D5EAFF;");
    ui.treeWidget_job_kill->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                               "alternate-background-color: #D5EAFF;");
    ui.treeWidget_job_kill->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                 "alternate-background-color: #D5EAFF;");
    ui.treeWidget_manager_user_view2->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                         "alternate-background-color: #D5EAFF;");
    ui.treeWidget_manager_user_view2->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                           "alternate-background-color: #D5EAFF;");
    ui.treeWidget_monitor_jobs->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                   "alternate-background-color: #D5EAFF;");
    ui.treeWidget_monitor_jobs->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                     "alternate-background-color: #D5EAFF;");
    ui.treeWidget_monitor_nodes->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                    "alternate-background-color: #D5EAFF;");
    ui.treeWidget_monitor_nodes->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                      "alternate-background-color: #D5EAFF;");
    ui.treeWidget_nodeViewer->verticalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                 "alternate-background-color: #D5EAFF;");
    ui.treeWidget_nodeViewer->horizontalScrollBar()->setStyleSheet("background-color: #ffd39b;"
                                                                   "alternate-background-color: #D5EAFF;");
    //    ui.pushButton_job_kill->setStyleSheet("QPushButton { margin: 1px; border-color: #0c457e; border-style: outset;border-radius: 3px;border-width: 1px;color: black;background-color: rbg(140,140,198);}" "QPushButton:checked {background-color: pink;}");
}

MainWindow::~MainWindow()
{
    closeSshClientSession();
    ftpThread->quit();//destroy ftp thread
    ftpThread->deleteLater();
    ftpWorker->deleteLater();

    manageThread->quit();
    manageThread->deleteLater();
    manageWorker->deleteLater();

}

void MainWindow::closeSshClientSession()
{

    client->shutdownShell();
    client->shutdownSftp();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);


}

void MainWindow::closeThreads()
{
    ftpThread->quit();//destroy ftp thread
    ftpThread->deleteLater();
    ftpWorker->deleteLater();

    manageThread->quit();
    manageThread->deleteLater();
    manageWorker->deleteLater();

    shellWorker->canceled_flag = true;


}

//create cpu ram indicator
void MainWindow::createCircleBar(){
    QGradientStops gradientPoints;
    gradientPoints << QGradientStop(0, Qt::green) << QGradientStop(0.5, Qt::yellow) << QGradientStop(1, Qt::red);
    QPalette p1;
    p1.setBrush(QPalette::AlternateBase, Qt::black);
    p1.setColor(QPalette::Text, Qt::yellow);
    QPalette p2(p1);
    p2.setBrush(QPalette::Base, Qt::lightGray);
    p2.setColor(QPalette::Text, Qt::magenta);
    p2.setColor(QPalette::Shadow, Qt::green);
    ui.widget_cpubar->setValue(0);
    ui.widget_cpubar->setPalette(p1);
    ui.widget_rambar->setValue(0);
    ui.widget_rambar->setPalette(p2);
}

void MainWindow::updateEventMessage(E_TYPE type,QString node_name,QString message)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(ui.treeWidget_bottomMessage);
    if(type==ALERT)
    {item->setText(0,QString("Alert"));item->setTextColor(0,Qt::red);}
    else if(type==EVENT)
    {item->setText(0,QString("Event"));item->setTextColor(0,Qt::green);}
    else if(type==DISK)
    {item->setText(0,QString("磁盘"));item->setTextColor(0,Qt::red);}
    else if(type==RAM)
    {item->setText(0,QString("内存"));item->setTextColor(0,Qt::red);}
    else if(type==MESSAGE)
    {item->setText(0,QString("消息"));item->setTextColor(0,Qt::green);}
    else if(type==ERR)
    {item->setText(0,QString("故障"));item->setTextColor(0,Qt::red);}

    item->setData(1,Qt::EditRole,QTime::currentTime());
    item->setText(2,node_name);
    item->setText(3,message);
}

void MainWindow::setupThreads(SshConfigure configure){

    ftpThread = new QThread;//create ftp thread
    ftpWorker = new FtpWorker(0,configure);//create ftpWorker
    updatorThread = new QThread;
    shellWorker = new ShellWorker(0,configure);
    manageThread = new QThread;
    manageWorker = new ManageWorker(0,configure);

    ftpWorker->moveToThread(ftpThread);//move worker to thread
    shellWorker->moveToThread(updatorThread);
    manageWorker->moveToThread(manageThread);

    /*************************************ftp***************************************/
    //connect sigal and slots
    //connect start signal to processer slot
    connect(this, SIGNAL(ftpDownloadStart(QString,QString)), ftpWorker, SLOT(processDownload(QString,QString)));
    connect(this, SIGNAL(ftpUploadStart(QString,QString)), ftpWorker, SLOT(processUpload(QString,QString)));
    connect(this,SIGNAL(ftpListDirStart(QString,int)),ftpWorker,SLOT(processListDirect(QString,int)));
    connect(this,SIGNAL(ftpRemoveFileStart(QString)),ftpWorker,SLOT(processRMFile(QString)));
    connect(this,SIGNAL(ftpMkDirStart(QString,QString)),ftpWorker,SLOT(processMkDir(QString,QString)));
    //connect thread finish signal to main process slot
    connect(ftpWorker, SIGNAL(finishDownload()), this, SLOT(processFtpDownloadFinishEvent()));
    connect(ftpWorker, SIGNAL(finishUpload()), this, SLOT(processFtpUploadFinishEvent()));
    connect(ftpWorker, SIGNAL(finishListDir(QList<QStringList>,int)), this, SLOT(processFtpListDirFinishEvent(QList<QStringList>,int)));
    connect(ftpWorker, SIGNAL(finishRMFile()), this, SLOT(processFtpRemoveFileFinishEvent()));
    connect(ftpWorker, SIGNAL(finishMkDir()), this, SLOT(processFtpMkDirFinishEvent()));
    //deal with destroy signals
    connect(ftpThread, SIGNAL (destroyed()), ftpWorker, SLOT (process1()));
    connect(ftpWorker, SIGNAL (finished()), ftpThread, SLOT (quit()));
    connect(ftpWorker, SIGNAL (finished()), ftpWorker, SLOT (deleteLater()));
    connect(ftpThread, SIGNAL (finished()), ftpThread, SLOT (deleteLater()));
    ftpThread->start();//start ftpThread
    /****************************************************************************/
    /*************************************shell***************************************/
    //connect
    connect(shellWorker,SIGNAL(hostTempratureFinished(int)),this,SLOT(updateHostTempGUI(int)));
    connect(shellWorker,SIGNAL(cpuFinished(QString)),this,SLOT(updateCPUGUI(QString)));
    connect(shellWorker,SIGNAL(ramFinished(QString)),this,SLOT(updateRAMGUI(QString)));
    connect(shellWorker,SIGNAL(diskFinished(QString)),this,SLOT(updateDISKGUI(QString)));
    connect(shellWorker,SIGNAL(dateFinished(QString)),this,SLOT(updateDATEGUI(QString)));
    connect(shellWorker,SIGNAL(uptimeFinished(QString)),this,SLOT(updateUPTIMEGUI(QString)));
    connect(shellWorker,SIGNAL(nodesFinished(QString)),this,SLOT(updateNODESGUI(QString)));
    connect(shellWorker,SIGNAL(jobsQSubFinished(QStringList,QStringList)),this,SLOT(updateJOBSGUI1(QStringList,QStringList)));
    connect(shellWorker,SIGNAL(jobsShowjobsFinished(QStringList,QStringList)),this,SLOT(updateJOBSGUI2(QStringList,QStringList)));
    connect(shellWorker,SIGNAL(connectionFailedSignal()),this,SLOT(processConnectionFailedEvent()));
    connect(shellWorker,SIGNAL(connectionSuccessSignal()),this,SLOT(processConnectionSuccessEvent()));



    //deal with destry signals
    connect(updatorThread, SIGNAL (destroyed()), shellWorker, SLOT (process()));
    connect(shellWorker, SIGNAL (finished()), updatorThread, SLOT (quit()));
    connect(shellWorker, SIGNAL (finished()), shellWorker, SLOT (deleteLater()));
    connect(updatorThread, SIGNAL (finished()), updatorThread, SLOT (deleteLater()));
    /*******************************************************************************/
    /*************************************manage***************************************/

    //connect signals with worker thread
    connect(this,SIGNAL(manageGetAllUserStart()),manageWorker,SLOT(getAllUser()));
    connect(this,SIGNAL(getQueueOfUserStart(QString)),manageWorker,SLOT(getQueueOfUser(QString)));
    connect(this,SIGNAL(getLimitedQueuesStart()),manageWorker,SLOT(getLimitedQueues()));
    connect(this,SIGNAL(addUserStartSignal(QString,QString,QString)),manageWorker,SLOT(addUser(QString,QString,QString)));
    connect(this,SIGNAL(getAllQueueInfosStart()),manageWorker,SLOT(getAllQueueDetails()));
    connect(this,SIGNAL(addQueueStartSignal(QueueAttributes)),manageWorker,SLOT(addQueue(QueueAttributes)));
    connect(this,SIGNAL(refreshStartSignal()),manageWorker,SLOT(refresh()));


    //connect finish signal with processing SLOT
    connect(manageWorker,SIGNAL(finishGetAllUser(QList<QStringList>)),this,SLOT(processManageGetUserFinishEvent(QList<QStringList>)));
    connect(manageWorker,SIGNAL(finishGetQueueOfUser(QHash<QString,QList<QStringList>>)),this,SLOT(processManageGetQueueOfUserFinishEvent(QHash<QString,QList<QStringList>>)));
    connect(manageWorker,SIGNAL(finishGetLimitedQueues(QStringList)),this,SLOT(processGetLimitedQueueFinishEvent(QStringList)));
    connect(manageWorker,SIGNAL(finishGetAllQueueInfos(QStringList,QList<QStringList>,QList<QList<QStringList>>)),this,SLOT(processGetAllQueueInfosFinishEvent(QStringList,QList<QStringList>,QList<QList<QStringList>>)));

    //deal with deconstruction signals
    connect(manageThread,SIGNAL(destroyed()),manageWorker,SLOT(process()));
    connect(manageWorker,SIGNAL(finished()),manageThread,SLOT(quit()));
    connect(manageWorker,SIGNAL(finished()),manageWorker,SLOT(deleteLater()));
    connect(manageThread,SIGNAL(finished()),manageThread,SLOT(deleteLater()));
    manageThread->start();
    /**************************************************************************/

}

void MainWindow::setupMenuAction()
{
    connect(this,SIGNAL(closedWindow()),qApp,SLOT(quit()));
    //setup menu bar action
    connect(ui.action_ChangeUser,SIGNAL(triggered()),this,SLOT(changeUserSlot()));
    connect(ui.action_Quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui.action_FullScreen,SIGNAL(triggered()),this,SLOT(showFullScreen()));
}

void MainWindow::setupClient(SshConfigure configure)
{
    //get configure
    this->m_configure=configure;
    //main thread client
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->m_configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();
    client->startSftp();
    client->executeShellCommand("sudo dmidecode",outputString);
    qDebug()<<"@12345654321";
    qDebug()<<QString::fromStdString(outputString);
}

void MainWindow::setupMac()
{
    //show mac address
    client->executeShellCommand("cat /sys/class/net/eth0/address",outputString);
    if(outputString!=""){
        ui.label_macshow->setText(QString::fromStdString(outputString).remove("\n"));
    }
}

void MainWindow::setupSystemVersion()
{
    client->executeShellCommand("lsb_release -a | grep Description | awk -F: '{print $2}'",outputString);
    if(outputString!="")
    {
        QString temp = QString::fromStdString(outputString).remove("\n");
        ui.label_sysversion_show->setText(temp);
    }
}

void MainWindow::setupQueue()
{
    //get queue string
    client->executeShellCommand("qstat -q",outputString);
    if(outputString!=""){
        //create regex
        QRegularExpression re("^\\b\\w+\\b");
        //iterate queuelist
        for(int i=5;i<QString::fromStdString(outputString).split("\n").size()-3;i++){
            //create match
            QRegularExpressionMatch match = re.match(QString::fromStdString(outputString).split("\n")[i]);
            //identify matched line
            if (match.hasMatch()) {
                //append queuelist
                queueList.append(match.captured(0));
                queueContentList.append(QString::fromStdString(outputString).split("\n")[i].split(QRegExp("[\\s]+")));


            }
        }

        //update queue list widget
        for(int j=0;j<queueList.size();j++){
            //add item to queue comboBox
            ui.comboBox_queue->addItem(queueList[j]);
        }


    }

}

void MainWindow::setupCurrentpath()
{
    client->executeShellCommand("pwd",outputString);
    if(!outputString.empty()){

        currentPathRemote = outputString;
        currentPathRemote.erase(std::remove(currentPathRemote.begin(), currentPathRemote.end(), '\n'), currentPathRemote.end());
    }
    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));
}
void MainWindow::setupDateAndUptime()
{
    client->executeShellCommand("date -d \"$(awk -F. '{print $1}' /proc/uptime) second ago\" +\"%Y-%m-%d %H:%M:%S\"",outputString);
    if(!outputString.empty())
        openTime = QString::fromStdString(outputString).remove("\n");
    ui.label_openTime->setText(openTime);

    client->executeShellCommand("cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf(\"%d/%d/%d/%d\",run_days,run_hour,run_minute,run_second)}'",outputString);
    if(outputString!=""){
        QStringList strList = QString::fromStdString(outputString).split("/");
        ui.label_RDay->setText(strList[0]);
        ui.label_RHour->setText(strList[1]);
        ui.label_RMin->setText(strList[2]);
    }
}

void MainWindow::setupHostAndIP()
{

    //show host ip address
    client->executeShellCommand("hostname -I | awk '{print $1}'",outputString);
    if(!outputString.empty()){
        ui.label_ipshow->setText(QString::fromStdString(outputString).remove("\n"));
    }


    client->executeShellCommand("hostname",outputString);
    if(!outputString.empty())
        ui.label_nameshow->setText(QString::fromStdString(outputString).remove("\n"));
}

void MainWindow::setupStorageDisplay()
{
    //make storage display
    client->executeShellCommand("df -h",outputString);//raw data
    if(outputString!=""){//data exists

        storageInfoList.clear();//reset widget
        //extract useful data
        QRegularExpression re("\\b\\d+.*");
        QRegularExpressionMatchIterator i = re.globalMatch(QString::fromStdString(outputString));
        while(i.hasNext()){
            QRegularExpressionMatch match = i.next();
            QString storageInfo = match.captured(0);
            storageInfoList<<storageInfo;

        }

        for(int i =0;i<storageInfoList.size();i++){
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow1_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow1_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_distShowRow1_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
                if(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt()>=80)
                {
                    //                        if(update_flag_s1 == true)
                    //                        {
                    updateEventMessage(DISK,"管理节点","/ 目录存储空间不足");
                    ui.pushButton_disk->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");
                    //                            update_flag_s1 = false;
                    //                        }

                }

            }
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/boot",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow2_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow2_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_diskShowRow2_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
                if(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt()>=80)
                {
                    //                    if(update_flag_s1 == true)
                    //                    {
                    updateEventMessage(DISK,"管理节点","/boot 目录存储空间不足");
                    ui.pushButton_disk->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");
                    //                        update_flag_s1 = false;
                    //                    }

                }
            }
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/home",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow3_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow3_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_diskShowRow3_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
                if(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt()>=80)
                {
                    //                    if(update_flag_s1 == true)
                    //                    {
                    updateEventMessage(DISK,"管理节点","/home 目录存储空间不足");
                    ui.pushButton_disk->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");
                    //                        update_flag_s1 = false;
                    //                    }

                }
            }

            //            update_flag_s1 = false;
        }

    }
}

void MainWindow::setupNodesDisplay()
{
    //get nodes info list
    client->executeShellCommand("pbsnodes",outputString);
    //identify unempty nodesinfo
    if(outputString!=""){
        //store nodes info big string as qstring
        nodesinfos = QString::fromStdString(outputString);
        //iterate all nodes
        for(int i=0;i<nodesinfos.split("\n\n").size();i++)
        {
            //store item in list of stringlist
            nodesList.append(nodesinfos.split("\n\n")[i].split(QRegExp("\\n[\\s]+")));
        }

        //clear main left nodes tree
        ui.treeWidget_nodeViewer->clear();
        //create root node1
        QTreeWidgetItem *mainNode = new QTreeWidgetItem(ui.treeWidget_nodeViewer);
        mainNode->setIcon(0,QIcon(":/Resources/temp/机柜.png"));
        mainNode->setText(0,"计算机集群");
        //create son node of node1
        QTreeWidgetItem *controlComputer = new QTreeWidgetItem(mainNode);
        controlComputer->setIcon(0,QIcon(":/Resources/node_32px.png"));
        controlComputer->setText(0,"管理节点");
        QTreeWidgetItem* cpuNode = new QTreeWidgetItem(mainNode);
        cpuNode->setIcon(0,QIcon(":/Resources/cpu_intel.png"));
        cpuNode->setText(0,"CPU节点");

        for(int j=0;j<nodesList.size()-1;j++){
            QTreeWidgetItem *CPUComputer = new QTreeWidgetItem(cpuNode);
            CPUComputer->setIcon(0,QIcon(":/Resources/cpu_intel.png"));
            CPUComputer->setText(0,nodesList[j][0]);
            CPUComputer->setText(1,"hello");
            CPUComputer->setText(2,"world");
        }

        QTreeWidgetItem *exchanger = new QTreeWidgetItem(mainNode);
        exchanger->setIcon(0,QIcon(":/Resources/wireless_router.png"));
        exchanger->setText(0,"交换机");

        QTreeWidgetItem *GPUNode = new QTreeWidgetItem(mainNode);
        GPUNode->setIcon(0,QIcon(":/Resources/temp/gpu.png"));
        GPUNode->setText(0,"GPU节点");

        //initilizing nodes counters
        isFree = true;
        usedCore=0;
        availableCore=0;
        totalCore=0;
        freeNodes=0;
        partUsedNodes=0;
        fullUsedNodes=0;
        downNodes=0;
        ui.treeWidget_monitor_nodes->clear();//clear the display

        //iterate all nodes for moniter tab display
        for (int i = 0 ;i<nodesList.size()-1;i++)
        {
            QTreeWidgetItem *nodeItem = new QTreeWidgetItem(ui.treeWidget_monitor_nodes);
            nodeItem->setText(0,nodesList[i][0]);
            for(int j=0;j<nodesList[i].size()-1;j++)
            {
                if(nodesList[i][j].split(" = ")[0].compare("np")==0){
                    totalCore = nodesList[i][j].split(" = ")[1].toInt();
                    //                    break;
                }
            }

            for(int j=0;j<nodesList[i].size()-1;j++)
            {
                if(nodesList[i][j].split(" = ")[0].compare("jobs")==1){
                    isFree = false;
                    //                    break;
                }
            }

            if(isFree==true){
                //wei 0
                usedCore = 0;
                availableCore = totalCore -usedCore;
                nodeItem->setText(3,QString::number(usedCore));
                nodeItem->setText(4,QString::number(availableCore));
                nodeItem->setTextColor(0,Qt::green);
                nodeItem->setTextColor(4,Qt::green);
            }

            //iterate all items of a node
            for(int j=0;j<nodesList[i].size()-1;j++){
                //identify busy nodes
                if(nodesList[i][j].split(" = ")[0].compare("jobs")==0){
                    usedCore = nodesList[i][j].split(" = ")[1].split(",").size();//get used cores count
                    availableCore = totalCore -usedCore;//calculate avaliable cores count
                    nodeItem->setText(3,QString::number(usedCore));//show counts
                    nodeItem->setText(4,QString::number(availableCore));
                    if(availableCore==0){
                        nodeItem->setTextColor(0,Qt::red);
                        nodeItem->setTextColor(3,Qt::red);
                        nodeItem->setTextColor(4,Qt::red);
                        fullUsedNodes++;
                    }
                    if(availableCore!=0){
                        nodeItem->setTextColor(0,Qt::blue);
                        nodeItem->setTextColor(3,Qt::red);
                        nodeItem->setTextColor(4,Qt::green);
                        partUsedNodes++;
                    }
                    //                    break;
                }
            }


        }

        //set counters display
        ui.label_freenodes->setText(QString::number(nodesList.size()-partUsedNodes-fullUsedNodes-1));
        ui.label_partusednodes->setText(QString::number(partUsedNodes));
        ui.label_fullusednodes->setText(QString::number(fullUsedNodes));
        ui.label_downnodes->setText(QString::number(downNodes));

        ui.label_MainServerCount->setText(QString::number(nodesList.size()-1));
        ui.label_NodeCount_up->setText(QString::number(nodesList.size()-partUsedNodes-fullUsedNodes-1));
        ui.label_NodeCount_down->setText(QString::number(partUsedNodes));

        //iterate all nodes for control tab display
        for (int i = 0 ;i<nodesList.size()-1;i++){
            QListWidgetItem *nodeItem = new QListWidgetItem(ui.listWidget_control_nodes);
            nodeItem->setText(nodesList[i][0]);
            if(nodesList[i][1].split(" = ")[1]=="free")
            {
                nodeItem->setBackgroundColor("#A6FFA6");
            }

            else if(nodesList[i][1].split(" = ")[1]=="down")
            {

                nodeItem->setBackgroundColor("#FF5809");
            }
            else
            {

                nodeItem->setBackgroundColor("#97CBFF");
            }
        }

    }
}

void MainWindow::setupFtp()
{
    // QToolBar* toolBar_ftp_A = new QToolBar(ui.frame_local);
    // QToolBar* toolBar_ftp_B = new QToolBar(ui.frame_remote);
    // toolBar_ftp_A->addAction(ui.actionupload);
    // toolBar_ftp_B->addAction(ui.actiondownload);
    updateFileList(ui.treeWidget,3);
    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget_job_file,2);
}

void MainWindow::setupCPUInfo()
{
    //get cpu cores
    int cpuCores;
    client->executeShellCommand("nproc",outputString);
    if(outputString!="")
    {
        cpuCores=QString::fromStdString(outputString).remove("\n").toInt();
        ui.label_CPUCoreShow->setText(QString::number(cpuCores));
    }
    client->executeShellCommand("cat /proc/cpuinfo | grep 'model name' | awk -F: '{print $2}'",outputString);
    ui.label_CPUTypeShow->setText(QString::fromStdString(outputString).split("\n")[0]);
    ui.label_CPUFreqShow->setText(QString::fromStdString(outputString).split("\n")[0].split(" ").last());

}



void MainWindow::setupRamInfo()
{
    //show ram usage
    client->executeShellCommand("free",outputString);
    if(outputString!=""){
        QRegularExpression re("\\b\\d.*");
        QRegularExpressionMatch match = re.match(QString::fromStdString(outputString));//get first match of ram info
        if(match.hasMatch()){
            if(match.captured(0).split(QRegExp("[\\s]+")).size()>=2){
                totalRam = match.captured(0).split(QRegExp("[\\s]+"))[0].toFloat();//get total ram
                ui.label_RamSizeShow->setText(QString::number(totalRam/1024/1024)+"GB");
            }
        }
    }
}

void MainWindow::setupStatusTracer()
{

    temp = status_increment_indicator;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStatusTracer()));
    timer->start(20000);

}

void MainWindow::setupMessageUpdateTimer()
{
    message_update_timer = new QTimer(this);
    connect(message_update_timer,SIGNAL(timeout()),this,SLOT(updateMessageUpdateTimerFlag()));
    message_update_timer->start(15000);
}

void MainWindow::updateMessageUpdateTimerFlag()
{
//    update_flag_s1 = true;
//    update_flag_s2 = true;
//    update_flag_s3 = true;
//    update_flag_s4 = true;
}

void MainWindow::updateStatusTracer()
{

    if(temp != status_increment_indicator)
    {
        isOnline = true;
        temp = status_increment_indicator;
    }

    else if(temp == status_increment_indicator)
    {
        isOnline = false;
        //        ui.label_connection_indicator->setText("offline");
        current_state_label_show.setText("  offline");
        current_state_label_show.setStyleSheet("color:red;");
    }

    getHostCpuFreqCache();
    ui.label_CPUFreqShow->setToolTip(host_cores_freq_cache);

}
void MainWindow::setupCurrentUser(QString input)
{
    //    ui.label_current_user->setText(input);
    current_user_label_show.setText(input);

}

void MainWindow::setupSSHConfigureInfo(SshConfigure configure)
{
    m_configure = configure;
}

void MainWindow::getHostCpuFreqCache()
{
    client->executeShellCommand("cat /proc/cpuinfo | grep 'cpu MHz'",outputString);
    host_cores_freq_cache = QString::fromStdString(outputString);
}
//setup ssh client session and initilizations
void MainWindow::setupSessionConfigure(SshConfigure configure)
{

    setupSSHConfigureInfo(configure);
    setupCurrentUser(QString::fromStdString(configure.user));
    setupThreads(configure);
    setupMenuAction();
    setupClient(configure);
    setupMac();
    setupSystemVersion();
    setupQueue();
    setupCurrentpath();
    setupDateAndUptime();
    setupHostAndIP();
    setupStorageDisplay();
    setupNodesDisplay();
    setupFtp();
    setupCPUInfo();
    setupRamInfo();
    setupStatusTracer();
    setupMessageUpdateTimer();
    // //display control tab node list
    updatorThread->start();//start shellTHread

    getHostCpuFreqCache();
    ui.label_CPUFreqShow->setToolTip(host_cores_freq_cache);


    emit manageGetAllUserStart();
    emit getLimitedQueuesStart();
    emit getAllQueueInfosStart();

    //setup ipc client
    setupIPCClient(configure);
}

void MainWindow::reconnect()
{
    setupCurrentUser(QString::fromStdString(m_configure.user));
    setupThreads(m_configure);
    setupClient(m_configure);
    setupMac();
    setupSystemVersion();
    setupQueue();
    setupCurrentpath();
    setupDateAndUptime();
    setupHostAndIP();
    setupStorageDisplay();
    setupNodesDisplay();
    setupFtp();
    setupCPUInfo();
    setupRamInfo();
    // //display control tab node list
    updatorThread->start();//start shellTHread
    emit manageGetAllUserStart();
    emit getLimitedQueuesStart();
    emit getAllQueueInfosStart();
}

void MainWindow::closeSession()
{

}

void MainWindow::refreshNodesList()
{
    hardware_hostname_list.clear();
}
void MainWindow::updateGetHardwareInfo()
{
    qDebug()<<"hardware get info updated";
    QString temp_str;
    QString temp_sysinfo;
    while (process.messageReceived())
    {
        std::unique_ptr<IpcMessage::IIpcMessage> msg = std::move(process.getOneMessage());
        SystemMonitorMessage::ISystemMonitorMessage* systemMessage =
                dynamic_cast<SystemMonitorMessage::ISystemMonitorMessage*>(msg.get());
        SystemMonitorMessage::ComputerNodeInfoReport* resp =
                dynamic_cast<SystemMonitorMessage::ComputerNodeInfoReport *>(systemMessage);

        //comuter i need you to extract each message's temprature information for me so as to judge if any nodes are beyond alert temprature

        temp_str = QString::fromStdString(resp->getHostName());
        std::stringstream str_sysInfoBriefly;
        str_sysInfoBriefly << resp->getSystemInfoBriefly();
        temp_sysinfo = QString::fromStdString(str_sysInfoBriefly.str());

        QString raw_temprature;
        QRegularExpression re6("temprature=..");
        QRegularExpressionMatch match_selectedNode_temprature =re6.match(temp_sysinfo);
        if(match_selectedNode_temprature.hasMatch())
        {
            raw_temprature = match_selectedNode_temprature.captured(0);
        }

        if(raw_temprature.contains("="))
        {
            int temp_nodeTemprature;
            temp_nodeTemprature = raw_temprature.split("=")[1].toInt();
            if(temp_nodeTemprature>=70&&update_flag_s4==true)
            {
                updateEventMessage(ALERT,temp_str,"节点温度超过70度！");
                ui.pushButton_temprature->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");

                update_flag_s4 = false;
            }
        }



        QString cpu_usage;
        std::stringstream str_cpuUsageInfo;//raw cpu usage data
        str_cpuUsageInfo << resp->getCpuUsageInfo();
        QString temp_cpuInfo = QString::fromStdString(str_cpuUsageInfo.str());
        QRegularExpression re("(?<=total=)[\\d]+");
        QRegularExpressionMatch match_cpu_total = re.match(temp_cpuInfo);
        if(match_cpu_total.hasMatch()){
            cpu_usage = match_cpu_total.captured(0);
        }

        QStringList temp_strList;
        temp_strList.append(temp_str);
        temp_strList.append(cpu_usage);
        if(hardware_hostname_list.isEmpty())
        {
            hardware_hostname_list.append(temp_strList);
        }
        bool temp_signal = false;
        foreach(QStringList each,hardware_hostname_list)
        {
            if(each.at(0).compare(temp_str)==0)
            {
                temp_signal = true;
                break;
            }

        }

        if(temp_signal==false)
        {
            hardware_hostname_list.append(temp_strList);
        }
        qDebug()<<hardware_hostname_list;

        //        if(!hardware_hostname_list.contains(temp_str))
        //        {
        //            hardware_hostname_list.append(temp_str);
        //        }
        std::cout << "-----------------------" << std::endl;
        if(resp->getHostName().compare(activated_node.toStdString())==0)
        {
            updateHardwareGUI(resp);
        }
    }
    makeHardwareNodesButtons(hardware_hostname_list);


}

void MainWindow::updateHardwareGUI(SystemMonitorMessage::ComputerNodeInfoReport* resp)
{
    int cpu_usage;//cpu usage
    int ram_usage;//ram usage

    std::stringstream str_stream;//raw system information for debug only
    str_stream << resp->getSystemInfoBriefly();//retrieve system info
    qDebug()<<"@777888";
    qDebug()<<QString::fromStdString(str_stream.str());//for debug use only

    std::stringstream str_process;//raw system info for display usage
    str_process << resp->getSystemInfoBriefly();//get
    QString temp_sys = QString::fromStdString(str_process.str());//transfer to qstring

    //----------------get total cpu usage and make a display--------------------//

    std::stringstream str_cpuUsageInfo;//raw cpu usage data
    str_cpuUsageInfo << resp->getCpuUsageInfo();
    QString temp_cpuInfo = QString::fromStdString(str_cpuUsageInfo.str());
    qDebug()<<temp_cpuInfo;
    QRegularExpression re("(?<=total=)[\\d]+");
    QRegularExpressionMatch match_cpu_total = re.match(temp_cpuInfo);
    if(match_cpu_total.hasMatch()){
        cpu_usage = match_cpu_total.captured(0).toInt();
    }
    updateCPUTotal(cpu_usage);
    //--------------------------------------------------------------------------//

    //-----------------calculate ram usage and make a display-----------------------//
    int memTotal;
    int memFree;
    QRegularExpression re3("(?<=memTotal=)[\\d]+(?= )");
    QRegularExpressionMatch match_ram_total = re3.match(temp_sys);
    if(match_ram_total.hasMatch())
    {
        memTotal = match_ram_total.captured(0).toInt();
    }

    QRegularExpression re4("(?<=memFree=)[\\d]+(?= )");
    QRegularExpressionMatch match4 = re4.match(temp_sys);
    if(match4.hasMatch())
    {
        memFree = match4.captured(0).toInt();
    }
    ram_usage = ((double)memTotal - (double)memFree)/(double)memTotal * 100;qDebug()<<"@2";
    qDebug()<<ram_usage;
    updateRamTotal(ram_usage);

    //-------------------------------------------------------------------------------//

    //----------------------process cpu-----------------------------------//
    ui.cpu_process->clear();

    QRegularExpression re2("(?<=psTop10CpuUsage=)[\\w\\W]+(?=\\n,)");
    QRegularExpressionMatch match_psTop10CpuProcess =re2.match(temp_sys);
    QString temp_process_cpu;
    if(match_psTop10CpuProcess.hasMatch()){

        temp_process_cpu = match_psTop10CpuProcess.captured(0);

    }
    qDebug()<<"@3";
    qDebug()<<temp_process_cpu.remove("[").remove("]").split("\n");
    QStringList processList_cpu = temp_process_cpu.remove("[").remove("]").split("\n");
    int maximumPropertySize = 5;
    for(int i = 0;i < activated_process_count;i++)
    {
        QStringList temp_str=processList_cpu[i].split(",");
        if(temp_str.size()>=maximumPropertySize)
        {

            QTreeWidgetItem* item = new QTreeWidgetItem(ui.cpu_process);
            item->setText(0,temp_str[0].split("=")[1]);
            item->setData(1,Qt::EditRole,temp_str[1].split("=")[1].toInt());
            item->setText(2,temp_str[2].split("=")[1]);
            item->setData(3,Qt::EditRole,temp_str[3].split("=")[1].toInt());
            item->setData(4,Qt::EditRole,temp_str[4].split("=")[1].toDouble());
        }
    }

//    foreach(QString each,processList_cpu)
//    {
//        QStringList temp_str=each.split(",");
//        if(temp_str.size()>=maximumPropertySize)
//        {
//            QTreeWidgetItem* item = new QTreeWidgetItem(ui.cpu_process);
//            item->setText(0,temp_str[0].split("=")[1]);
//            item->setData(1,Qt::EditRole,temp_str[1].split("=")[1].toInt());
//            item->setText(2,temp_str[2].split("=")[1]);
//            item->setData(3,Qt::EditRole,temp_str[3].split("=")[1].toInt());
//            item->setData(4,Qt::EditRole,temp_str[4].split("=")[1].toDouble());

//        }


//    }

    //-------------------------------------------------------------------//

    //--------------------process ram------------------------------//

    ui.ram_process->clear();
    QRegularExpression re5("(?<=psTop10MemoryUsage=)[\\w\\W]+(?=\\nnvidia)");
    QRegularExpressionMatch match_psTop10RamProcess =re5.match(temp_sys);
    QString temp_process_mem;
    if(match_psTop10RamProcess.hasMatch()){

        temp_process_mem = match_psTop10RamProcess.captured(0);

    }
    qDebug()<<"@4";
    qDebug()<<temp_process_mem.remove("[").remove("]").split("\n");
    QStringList processList_mem = temp_process_mem.remove("[").remove("]").split("\n");
    foreach(QString each,processList_mem)
    {
        QStringList temp_str=each.split(",");
        if(temp_str.size()>=maximumPropertySize)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(ui.ram_process);
            item->setText(0,temp_str[0].split("=")[1]);
            item->setData(1,Qt::EditRole,temp_str[1].split("=")[1].toInt());
            item->setText(2,temp_str[2].split("=")[1]);
            item->setData(3,Qt::EditRole,temp_str[3].split("=")[1].toInt());
            item->setData(4,Qt::EditRole,temp_str[4].split("=")[1].toInt());

        }


    }


    //---------------------------------------------------------------//

    //----------------------------cpu history------------------------//
    x.append(increamter);
    y.append(cpu_usage);
    ui.plot_cpuHistory->graph(0)->setData(x,y);

    ui.plot_cpuHistory->xAxis->setRange(-50+increamter,0+increamter);
    ui.plot_cpuHistory->replot();

    //----------------------------------------------------------------//

    //----------------------------ram history-------------------------//
    x1.append(increamter);
    y1.append(ram_usage);
    ui.plot_ramUsageHistory->graph(0)->setData(x1,y1);

    ui.plot_ramUsageHistory->xAxis->setRange(-50+increamter,0+increamter);
    ui.plot_ramUsageHistory->replot();
    increamter+=1;
    //----------------------------------------------------------------//


    //--------------------------------show selected node's tempreature-----------------//
    //computer, i want you to extract that information for me, you know.
    QString raw_temprature;
    QRegularExpression re6("temprature=..");
    QRegularExpressionMatch match_selectedNode_temprature =re6.match(temp_sys);
    if(match_selectedNode_temprature.hasMatch())
    {
        raw_temprature = match_selectedNode_temprature.captured(0);
    }

    qDebug()<<"@991";
    qDebug()<<raw_temprature;
    if(raw_temprature.contains("="))
    {
        ui.label_selectedNodes_hardware_temprature->setText("温度:\n"+raw_temprature.split("=")[1]);
        ui.label_selectedNodes_hardware_temprature->setStyleSheet("color: rgb(0, 0, 255);");

    }


    //--------------------------------process GPU informations-----------------------//



    //-------------------------------------------------------------------------------//

}

void MainWindow::plotHistoryRangeReset()
{
    increamter =1 ;
    x.clear();
    y.clear();
    x1.clear();
    y1.clear();

}

void MainWindow::makeHardwareNodesButtons(QList<QStringList> list)
{
    ui.listWidget_nodes_hardware->clear();
    foreach(QStringList each,list)
    {
        QListWidgetItem* item = new QListWidgetItem(ui.listWidget_nodes_hardware);
        item->setText(each.at(0));
        if(each.at(1).toInt()<10)
            item->setBackground(Qt::green);
        else if(each.at(1).toInt()>=10&&each.at(1).toInt()<80)
            item->setBackground(Qt::blue);
        else if(each.at(1).toInt()>=80)
            item->setBackground(Qt::red);

    }
}

void MainWindow::setupIPCClient(SshConfigure configure)
{
//    SshConfigure temp = configure;
    process.start();
    timer_hardware_getInfo = new QTimer;
    timer_hardware_getInfo->setInterval(500);
    connect(timer_hardware_getInfo,SIGNAL(timeout()),this,SLOT(updateGetHardwareInfo()));
    timer_hardware_getInfo->start();

}

//navigation button event handler
void MainWindow::on_pushButton_job_kill_clicked(){
    ui.stackedWidget_job->setCurrentIndex(0);
    ui.pushButton_job_kill->setChecked(true);
    ui.pushButton_job_submit->setChecked(false);
    ui.pushButton_job_file->setChecked(false);
}

void MainWindow::on_pushButton_job_submit_clicked(){
    ui.stackedWidget_job->setCurrentIndex(1);
    ui.pushButton_job_submit->setChecked(true);
    ui.pushButton_job_kill->setChecked(false);
    ui.pushButton_job_file->setChecked(false);
}
void MainWindow::on_pushButton_job_file_clicked(){
    ui.stackedWidget_job->setCurrentIndex(2);
    ui.pushButton_job_file->setChecked(true);
    ui.pushButton_job_submit->setChecked(false);
    ui.pushButton_job_kill->setChecked(false);
}
void MainWindow::on_pushButton_monitor_node_clicked()
{
    ui.stackedWidget_monior->setCurrentIndex(0);
    ui.pushButton_monitor_node->setChecked(true);
    ui.pushButton_monitor_jobs->setChecked(false);
//    ui.pushButton_monitor_GPU->setChecked(false);
//    ui.pushButton_monitor_IBCard->setChecked(false);

}
void MainWindow::on_pushButton_monitor_jobs_clicked()
{
    ui.stackedWidget_monior->setCurrentIndex(1);
    ui.pushButton_monitor_node->setChecked(false);
    ui.pushButton_monitor_jobs->setChecked(true);
//    ui.pushButton_monitor_GPU->setChecked(false);
//    ui.pushButton_monitor_IBCard->setChecked(false);
}


void MainWindow::on_pushButton_control_shutdownpage_clicked()
{
    ui.stackedWidget_control->setCurrentIndex(0);
    ui.pushButton_control_shutdownpage->setChecked(true);
    ui.pushButton_control_userpage->setChecked(false);
    ui.pushButton_control_queuepage->setChecked(false);
    ui.pushButton_control_computingtimepage->setChecked(false);
}
void MainWindow::on_pushButton_control_userpage_clicked(){
    ui.stackedWidget_control->setCurrentIndex(1);
    ui.pushButton_control_shutdownpage->setChecked(false);
    ui.pushButton_control_userpage->setChecked(true);
    ui.pushButton_control_queuepage->setChecked(false);
    ui.pushButton_control_computingtimepage->setChecked(false);
}
void MainWindow::on_pushButton_control_queuepage_clicked(){
    ui.stackedWidget_control->setCurrentIndex(2);
    ui.pushButton_control_shutdownpage->setChecked(false);
    ui.pushButton_control_userpage->setChecked(false);
    ui.pushButton_control_queuepage->setChecked(true);
    ui.pushButton_control_computingtimepage->setChecked(false);
}
void MainWindow::on_pushButton_control_computingtimepage_clicked(){
    ui.stackedWidget_control->setCurrentIndex(3);
    ui.pushButton_control_shutdownpage->setChecked(false);
    ui.pushButton_control_userpage->setChecked(false);
    ui.pushButton_control_queuepage->setChecked(false);
    ui.pushButton_control_computingtimepage->setChecked(true);
}

//putty launcher
void MainWindow::on_pushButton_4_clicked()
{


    if (layout != nullptr)
    {
        delete layout;
    }


    m_process = new QProcess(this);
    QString cmd = "putty.exe";
    QStringList args;
    args.append("-pw");
    args.append(QString::fromStdString(m_configure.password));
    args.append(QString::fromStdString(m_configure.user)+"@"+QString::fromStdString(m_configure.host));

    m_process->start(cmd,args);

}


//generate pbs script
void MainWindow::on_pushButton_job_submit_makescript_clicked()
{
    //choose submit mode 1
    if(ui.radioButton_parameter_by_nodenum->isChecked()){
        //get script varables
        nodesNum = QString::number(ui.spinBox_nodeNum->value());
        coreNum = QString::number(ui.spinBox_coreNum->value());
        jobName = ui.lineEdit_job_name->text();
        queueName = ui.comboBox_queue->currentText();
        outputLog = ui.lineEdit_job_submit_logname->text();
        walltime = ui.spinBox_hour->text()+":"+ui.spinBox_minite->text()+":00";

        //make script
        if(ui.radioButton_vasp->isChecked()){
            script= "#!/bin/sh\n#PBS -l nodes="+nodesNum+":ppn="+coreNum+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU=`wc -l < $PBS_NODEFILE`\ncd $PBS_O_WORKDIR\nmpirun -hostfile $PBS_NODEFILE -np $NCPU vasp";

        }
        else if(ui.radioButton_nanodcal->isChecked()){
            script= "#!/bin/sh\n#PBS -l nodes="+nodesNum+":ppn="+coreNum+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU=`wc -l < $PBS_NODEFILE`\ncd $PBS_O_WORKDIR\nmpirun -hostfile $PBS_NODEFILE -npernode 4 matlab -nodisplay -r \"nanodcal -parallel -doexit input.txt\"";

        }
        else if(ui.radioButton_others->isChecked()){
            script= "#!/bin/sh\n#PBS -l nodes="+nodesNum+":ppn="+coreNum+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU=`wc -l < $PBS_NODEFILE`\ncd $PBS_O_WORKDIR\nmpirun -hostfile $PBS_NODEFILE -np $NCPU "+ui.lineEdit_exec_others->text()+"";

        }

        //show script
        ui.textBrowser_job_submit_show->setText(script);
        //show qsub command
        ui.textBrowser_job_qsubCommand->setText(QString::fromStdString("qsub "+currentPathRemote+"/temp.pbs"));
        //make local temp
        QFile file("temp.pbs");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate))
        {
            QTextStream out(&file);
            out << script;
        }
        //clean remote temp
        client->executeShellCommand("rm "+currentPathRemote+"/temp.pbs",outputString);
        //upload to user root directory
        client->putFile("temp.pbs",currentPathRemote);
        //convert win doc to unix doc
        client->executeShellCommand("dos2unix "+currentPathRemote+"/temp.pbs",outputString);



    }
    //choose submit mode 2
    else if(ui.radioButton_parameter_byNodeName->isChecked()){

        QString qstr2 = ui.lineEdit_jobsubmit_nodesList->text();
        jobName = ui.lineEdit_jobsubmit_taskname2->text();
        queueName = ui.comboBox_queue->currentText();
        outputLog = ui.lineEdit_job_submit_logname->text();
        walltime = ui.spinBox_hour->text()+":"+ui.spinBox_minite->text()+":00";


        qstr2.replace(":",":ppn=");
        //make script
        if(ui.radioButton_vasp->isChecked()){
            //nodes=comput16:ppn=16+comput15:ppn=16
            script= "#!/bin/sh\n#PBS -l nodes="+qstr2+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU='wc -l < $PBS_NODEFILE'\ncd $PBS_O_WORKDIR\nsource /public/software/mpi/openmpi/1.6.5/intel/mpi.sh\nmpirun -hostfile $PBS_NODEFILE -np $NCPU vasp";

        }
        else if(ui.radioButton_nanodcal->isChecked()){
            script= "#!/bin/sh\n#PBS -l nodes="+qstr2+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU='wc -l < $PBS_NODEFILE'\ncd $PBS_O_WORKDIR\nmpirun -hostfile $PBS_NODEFILE -npernode 4 matlab -nodisplay -r \"nanodcal -parallel -doexit input.txt\"";

        }
        else if(ui.radioButton_others->isChecked()){
            script= "#!/bin/sh\n#PBS -l nodes="+qstr2+"\n#PBS -N "+jobName+"\n#PBS -o ./"+outputLog+".log\n#PBS -e ./err.log\n#PBS -l walltime="+walltime+"\n#PBS -q "+queueName+"\nNCPU='wc -l < $PBS_NODEFILE'\ncd $PBS_O_WORKDIR\nsource /public/software/mpi/openmpi/1.6.5/intel/mpi.sh\nmpirun -hostfile $PBS_NODEFILE -np $NCPU "+ui.lineEdit_exec_others->text()+"";

        }

        //show script
        ui.textBrowser_job_submit_show->setText(script);
        //show qsub command
        ui.textBrowser_job_qsubCommand->setText(QString::fromStdString("qsub "+currentPathRemote+"/temp.pbs"));
        //make local temp
        QFile file("temp.pbs");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate))
        {
            QTextStream out(&file);
            out << script;
        }
        //clean remote temp
        client->executeShellCommand("rm "+currentPathRemote+"/temp.pbs",outputString);
        //upload to user root directory
        client->putFile("temp.pbs",currentPathRemote);
        //convert win doc to unix doc
        client->executeShellCommand("dos2unix "+currentPathRemote+"/temp.pbs",outputString);

    }

}



//submit a job
void MainWindow::on_pushButton_job_submit_submit_clicked()
{

    //clacify script mode: create new
    if(ui.textBrowser_job_qsubCommand->toPlainText().compare(QString::fromStdString("qsub "+currentPathRemote+"/temp.pbs"))==0){
        //submit const char *
        client->executeShellCommand("cd "+currentPathRemote+" && "+ui.textBrowser_job_qsubCommand->toPlainText().toStdString(),outputString);
        if(!QString::fromStdString(outputString).isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("作业已提交: "+QString::fromStdString(outputString));
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("作业提交失败: "+QString::fromStdString(outputString));
            msgBox.exec();
        }

    }

    //goto selected script mode
    else{
        //submit const char *
        client->executeShellCommand("cd "+currentPathRemote+" && "+ui.textBrowser_job_qsubCommand->toPlainText().toStdString(),outputString);
        if(!QString::fromStdString(outputString).isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("作业已提交: "+QString::fromStdString(outputString));
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("作业提交失败: "+QString::fromStdString(outputString));
            msgBox.exec();
        }

    }


}

//refresh joblist in job tab
void MainWindow::on_pushButton_job_kill_refresh_clicked()
{

    ui.treeWidget_job_kill->clear();
    inputString = getJobListByuser;
    client->executeShellCommand(inputString, outputString);
    QStringList jobsList;
    if(!outputString.empty())
        jobsList=QString::fromStdString(outputString).split("\n");


    if(outputString!=""){
        for(int i=5;i<jobsList.size()-1;i++){

            if(jobsList[i].split(QRegExp("[\\s]+")).size()>10){
                QTreeWidgetItem *job = new QTreeWidgetItem(ui.treeWidget_job_kill);
                job->setText(0,jobsList[i].split(QRegExp("[\\s]+"))[0]);
                job->setText(1,jobsList[i].split(QRegExp("[\\s]+"))[1]);
                job->setText(2,jobsList[i].split(QRegExp("[\\s]+"))[2]);
                job->setText(3,jobsList[i].split(QRegExp("[\\s]+"))[3]);
                job->setText(4,jobsList[i].split(QRegExp("[\\s]+"))[5]);
                job->setText(5,jobsList[i].split(QRegExp("[\\s]+"))[6]);
                job->setText(6,jobsList[i].split(QRegExp("[\\s]+"))[10]);
                job->setText(7,jobsList[i].split(QRegExp("[\\s]+"))[9]);

                if(jobsList[i].split(QRegExp("[\\s]+"))[9].compare("R")==0)
                    job->setTextColor(7,Qt::green);
                if(jobsList[i].split(QRegExp("[\\s]+"))[9].compare("Q")==0)
                    job->setTextColor(7,Qt::red);

                ui.treeWidget_job_kill->addTopLevelItem(job);
            }

        }

    }
}

//save script changes
void MainWindow::on_pushButton_job_submit_save_clicked()
{
    if(ui.textBrowser_job_qsubCommand->toPlainText().compare(QString::fromStdString("qsub "+currentPathRemote+"/temp.pbs"))==0){
        script=ui.textBrowser_job_submit_show->toPlainText();

        QFile file("temp.pbs");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate))
        {
            QTextStream out(&file);
            out << script;
        }


        client->executeShellCommand("rm "+currentPathRemote+"/temp.pbs",outputString);

        client->putFile("temp.pbs",currentPathRemote);


        client->executeShellCommand("dos2unix "+currentPathRemote+"/temp.pbs",outputString);
    }
    else{
        QString fileName;
        if(!ui.label_job_submit_selectedScript->text().isEmpty())
        {
            fileName = ui.label_job_submit_selectedScript->text().split(":")[1];//qstring
            script=ui.textBrowser_job_submit_show->toPlainText();

            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate))
            {
                QTextStream out(&file);
                out << script;
            }


            client->executeShellCommand("rm "+currentPathRemote+"/"+fileName.toStdString(),outputString);

            client->putFile(fileName.toStdString(),currentPathRemote);


            client->executeShellCommand("dos2unix "+currentPathRemote+"/"+fileName.toStdString(),outputString);
        }
        else
        {

        }



    }


}


//kill job in job tab
void MainWindow::on_pushButton_job_kill_del_clicked()
{

    int length;length=ui.treeWidget_job_kill->selectedItems().count();
    QString jobName_del;
    if(length>0){
        for(int i=0;i<length;i++){

            jobName_del=ui.treeWidget_job_kill->selectedItems().at(i)->text(0);

            QRegularExpression re("^\\d+");
            QRegularExpressionMatch match = re.match(jobName_del);
            if(match.hasMatch()){
                jobDelCommand=("qdel "+match.captured(0)).toLatin1().data();
                client->executeShellCommand(jobDelCommand,outputString);
            }

        }

    }

}


//set filepath view
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(model->isDir(index)){

        localDir.cd(index.data().toString());
        ui.treeView->setRootIndex(model->index(localDir.absolutePath()));
        ui.lineEdit_ftp_localPath->setText(localDir.absolutePath());
        filePathLocal = localDir.absolutePath();
    }
    else
    {
        fileInfo=model->fileInfo(index);
        filePathLocal = localDir.absolutePath();


    }
}

//ftp download
void MainWindow::on_pushButton_clicked()
{
    //clacify if an item is selected
    if(!ui.treeWidget->currentItem()->text(0).toStdString().empty()&&!filePathLocal.isEmpty()){
        if(!isDir(ui.treeWidget->currentItem()->text(0)))
        {//identify if selected item is dir
            speedCalculatorThread = new QThread;
            speedWorker = new SpeedCalculator(0,m_configure);
            speedWorker->moveToThread(speedCalculatorThread);
            connect(ftpWorker, SIGNAL(finishDownload()), speedWorker, SLOT(process()));
            //connect start signal to process slot
            connect(this,SIGNAL(downloadSpeedMonitingStart(QString,QString,QString)),speedWorker,SLOT(processDownloadSpeed(QString,QString,QString)));
            //connect worker  signal to main process slot
            connect(speedWorker,SIGNAL(getDownloadSpeedSignal(int,qint64)),this,SLOT(displayDownloadSpeed(int,qint64)));
            //deal with destroy signals
            connect(speedCalculatorThread,SIGNAL(destroyed()),speedWorker,SLOT(process()));
            connect(speedWorker,SIGNAL(finished()),speedCalculatorThread,SLOT(quit()));
            connect(speedWorker,SIGNAL(finished()),speedWorker,SLOT(deleteLater()));
            connect(speedCalculatorThread,SIGNAL(finished()),speedCalculatorThread,SLOT(deleteLater()));
            speedCalculatorThread->start();

            emit ftpDownloadStart(QString::fromStdString(currentPathRemote)+"/"+ui.treeWidget->currentItem()->text(0),filePathLocal);//fire download start signal
            emit downloadSpeedMonitingStart(QString::fromStdString(currentPathRemote),filePathLocal,ui.treeWidget->currentItem()->text(0));
            ui.pushButton->setText("下载中...");//close button
            ui.pushButton->setEnabled(false);//close button
        }
        else//show warning if selected file is directory
        {
            QMessageBox msg;
            msg.setText("无法下载文件夹");
            msg.exec();
        }

    }



}

void MainWindow::displayDownloadSpeed(int speed, qint64 percent)
{
    ui.pushButton->setText("woho");
    ui.pushButton->setText("下载速度: "+QString::number(speed/1024)+"KB/S  下载进度: %"+QString::number(percent));
}

//process ftp download finish event
void MainWindow::processFtpDownloadFinishEvent(){
    model->refresh();
    ui.pushButton->setText("下载");//open button
    ui.pushButton->setEnabled(true);//open button
}

void MainWindow::processConnectionFailedEvent()
{

    //    ui.label_connection_indicator->setText("offline");
    current_state_label_show.setText("offline");
    current_state_label_show.setStyleSheet("color:red;");
}

void MainWindow::processConnectionSuccessEvent()
{

    //    ui.label_connection_indicator->setText("online");
    current_state_label_show.setText("online");
    current_state_label_show.setStyleSheet("color:green;");
}
//process ftp upload finish event
void MainWindow::processFtpUploadFinishEvent(){


    updateFileList(ui.treeWidget,1);
    ui.pushButton_3->setText("上传");
    ui.pushButton_3->setEnabled(true);

}

//process list dir finish event
void MainWindow::processFtpListDirFinishEvent(QList<QStringList> qlist,int i){
    temp_ptr = nullptr;
    temp_ptr2 = nullptr;
    QList<QStringList> m_list = qlist;
    clock_t begin,end;
    double seconds;
    switch(i){
    case 1: {
        ui.treeWidget_jobsubmitfile->clear();
        if(m_list.size()>1){
            for( int i =1;i<m_list.size();i++){//iterate filelist
                QTreeWidgetItem *file = new QTreeWidgetItem(ui.treeWidget_jobsubmitfile);
                if(m_list[i][1].compare("1")==0)
                {
                    file->setIcon(0,QIcon(":/Resources/file.png"));
                }
                else if (m_list[i][0].at(0)=="d")
                {
                    file->setIcon(0,QIcon(":/Resources/dir.png"));
                }
                file->setText(0,m_list[i][8]);
                if(m_list[i][4].toInt()>=1048576){file->setText(1,QString::number(m_list[i][4].toInt()/1048576)+QString(" MB"));}
                else if(m_list[i][4].toInt()<1048576 && m_list[i][4].toInt()>=1024){file->setText(1,QString::number(m_list[i][4].toInt()/1024)+QString(" KB"));}
                else if(m_list[i][4].toInt()<1024){file->setText(1,QString::number(m_list[i][4].toInt())+QString(" Bytes"));}
                file->setText(2,m_list[i][5]+" "+m_list[i][6]+" "+m_list[i][7]);
                file->setText(3,m_list[i][2]);
                file->setText(4,m_list[i][3]);
                file->setText(5,m_list[i][0]);

                ui.treeWidget_jobsubmitfile->addTopLevelItem(file);
                if(!ui.treeWidget_jobsubmitfile->currentItem()){
                    ui.treeWidget_jobsubmitfile->setCurrentItem(ui.treeWidget_jobsubmitfile->topLevelItem(0));
                    ui.treeWidget_jobsubmitfile->setEnabled(true);
                }


            }
        }

        break;
    }
    case 2:{
        ui.treeWidget_job_file->clear();
        if(m_list.size()>1){
            for( int i =1;i<m_list.size();i++){//iterate filelist
                QTreeWidgetItem *file = new QTreeWidgetItem(ui.treeWidget_job_file);
                if(m_list[i][1].compare("1")==0)
                {
                    file->setIcon(0,QIcon(":/Resources/file.png"));
                }
                else if (m_list[i][0].at(0)=="d")
                {
                    file->setIcon(0,QIcon(":/Resources/dir.png"));
                }
                file->setText(0,m_list[i][8]);
                if(m_list[i][4].toInt()>=1048576){file->setText(1,QString::number(m_list[i][4].toInt()/1048576)+QString(" MB"));}
                else if(m_list[i][4].toInt()<1048576 && m_list[i][4].toInt()>=1024){file->setText(1,QString::number(m_list[i][4].toInt()/1024)+QString(" KB"));}
                else if(m_list[i][4].toInt()<1024){file->setText(1,QString::number(m_list[i][4].toInt())+QString(" Bytes"));}
                file->setText(2,m_list[i][5]+" "+m_list[i][6]+" "+m_list[i][7]);
                file->setText(3,m_list[i][2]);
                file->setText(4,m_list[i][3]);
                file->setText(5,m_list[i][0]);

                ui.treeWidget_job_file->addTopLevelItem(file);
                if(!ui.treeWidget_job_file->currentItem()){
                    ui.treeWidget_job_file->setCurrentItem(ui.treeWidget_job_file->topLevelItem(0));
                    ui.treeWidget_job_file->setEnabled(true);
                }


            }
        }
        break;
    }
    case 3:{
        begin = clock();
        ui.treeWidget->clear();
        if(m_list.size()>1){
            for( int i =1;i<m_list.size();i++){//iterate filelist
                QTreeWidgetItem *file = new QTreeWidgetItem(ui.treeWidget);
                if(m_list[i][1].compare("1")==0)
                {
                    file->setIcon(0,QIcon(":/Resources/file.png"));
                }
                else if (m_list[i][0].at(0)=="d")
                {
                    file->setIcon(0,QIcon(":/Resources/dir.png"));
                }

//                //get system icon
//                QFileInfo fi(m_list[i][8]);
//                QString name = fi.fileName();
//                qDebug()<<"@hookerhereok";
//                qDebug()<<name;
//                QFileIconProvider iconSource;
//                QIcon icon = iconSource.icon(fi);
//                file->setIcon(0,icon);


                file->setText(0,m_list[i][8]);
                if(m_list[i][4].toInt()>=1048576){file->setText(1,QString::number(m_list[i][4].toInt()/1048576)+QString(" MB"));}
                else if(m_list[i][4].toInt()<1048576 && m_list[i][4].toInt()>=1024){file->setText(1,QString::number(m_list[i][4].toInt()/1024)+QString(" KB"));}
                else if(m_list[i][4].toInt()<1024){file->setText(1,QString::number(m_list[i][4].toInt())+QString(" Bytes"));}
                file->setText(2,m_list[i][5]+" "+m_list[i][6]+" "+m_list[i][7]);
                file->setText(3,m_list[i][2]);
                file->setText(4,m_list[i][3]);
                file->setText(5,m_list[i][0]);

                ui.treeWidget->addTopLevelItem(file);
                if(!ui.treeWidget->currentItem()){
                    ui.treeWidget->setCurrentItem(ui.treeWidget->topLevelItem(0));
                    ui.treeWidget->setEnabled(true);
                }


            }
        }
        end = clock();
        seconds = (end - begin) / (double)CLOCKS_PER_SEC;

        break;

    }


    }
}
//process rm file finish event
void MainWindow::processFtpRemoveFileFinishEvent(){

}

void MainWindow::processFtpMkDirFinishEvent()
{
    updateFileList(ui.treeWidget_jobsubmitfile,3);
    updateFileList(ui.treeWidget_job_file,2);
    updateFileList(ui.treeWidget,1);
}
void MainWindow::processManageGetUserFinishEvent(QList<QStringList> s)
{
    userList = s;

    ui.listWidget_manager_user_view1->clear();
    foreach(QStringList temp_item,s)
    {

        ui.listWidget_manager_user_view1->addItem(temp_item[0]);
    }
}

void MainWindow::processManageGetQueueOfUserFinishEvent(QHash<QString,QList<QStringList>> s)
{
    ui.treeWidget_manager_user_view2->clear();
    //in what way to show all queue info in to widget
    QList<QStringList> temp_list;
    QString temp_name;
    QHashIterator<QString, QList<QStringList>> i(s);
    while (i.hasNext()) {
        i.next();
        temp_name = i.key();
        temp_list = i.value();
        QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget_manager_user_view2);
        item->setText(0,temp_name);
        foreach(QStringList each,temp_list)
        {
            if(each[0]=="resources_max.nodes")
            {
                item->setData(1,Qt::DisplayRole,each[1].toInt());
                break;

            }
            else
            {
                item->setText(1,tr("无限制"));
            }
            if(each[0]=="max_running")
            {
                item->setData(2,Qt::DisplayRole,each[1].toInt());
                break;

            }
            else
            {
                item->setText(2,tr("无限制"));
            }

            if(each[0]=="resources_max.ncpus")
            {
                item->setData(3,Qt::DisplayRole,each[1].toInt());
                break;

            }
            else
            {
                item->setText(3,tr("无限制"));
            }
        }

    }


}

void MainWindow::processGetLimitedQueueFinishEvent(QStringList s)
{

    foreach(QString each,s)
    {
        ui.listWidget_showLimitedQueues->addItem(each);
    }
}

void MainWindow::processGetAllQueueInfosFinishEvent(QStringList queueList,QList<QStringList> queueContentList,QList<QList<QStringList>> queuePBSInfos)
{
    ui.treeWidget_control_queue_view->clear();

    QStringList queueList_ = queueList;
    QList<QStringList> queueContentList_ = queueContentList;
    QList<QList<QStringList>> queuePBSInfos_ = queuePBSInfos;
    for(int i = 0; i< queueList_.size();i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget_control_queue_view);
        setQueueName(item,i,queueList_);
        setQueuePriority(item,i,queuePBSInfos_);
        setQueueState(item,i,queueContentList_);
        setQueueUsability(item,i,queuePBSInfos_[i]);

    }
}
void MainWindow::setQueueUsability(QTreeWidgetItem *item,int i,QList<QStringList> queuePBSInfos)
{
    foreach(QStringList each,queuePBSInfos)
    {
        if(each[0].compare(QString("resources_max.nodes"))==0)
        {
            item->setText(4,each[1]);
            break;
        }
        else
            item->setText(4,QString("无限制"));
    }
    foreach(QStringList each,queuePBSInfos)
    {
        if(each[0].compare(QString("max_running"))==0)
        {
            item->setText(5,each[1]);
            break;
        }
        else
            item->setText(5,QString("无限制"));
    }foreach(QStringList each,queuePBSInfos)
    {
        if(each[0].compare(QString("resources_max.ncpus"))==0)
        {
            item->setText(6,each[1]);
            break;
        }
        else
            item->setText(6,QString("无限制"));
    }

}
void MainWindow::setQueueName(QTreeWidgetItem *item,int i,QStringList queueList)
{
    item->setText(0,queueList[i]);
}

void MainWindow::setQueuePriority(QTreeWidgetItem *item,int i,QList<QList<QStringList>> queuePBSInfos)
{
    if(hasProperty(queuePBSInfos[i],QString("priority")))
    {
        foreach(QStringList each, queuePBSInfos[i])
        {
            if(each[0].compare("priority")==0)
                item->setText(1,each[1]);
            break;
        }
    }
    else
        item->setText(1,"无");
}

bool MainWindow::hasProperty(QList<QStringList> queuePBSInfos,QString str)
{
    foreach(QStringList each, queuePBSInfos)
    {
        if(each[0].compare(str)==0)
            return true;
    }
    return false;
}

void MainWindow::setQueueState(QTreeWidgetItem *item,int i,QList<QStringList> queueContentList_)
{
    item->setText(2,queueContentList_[i][5]);
    item->setText(3,queueContentList_[i][6]);

}

//ftp upload
void MainWindow::on_pushButton_3_clicked()
{
    //judge if file selected
    if(!filePathLocal.isEmpty()){
        client->executeShellCommand("cd "+currentPathRemote+" && ls -l | awk '/"+fileInfo.fileName().toStdString()+"$/'",outputString);
        if(outputString!=""){
            QMessageBox::StandardButton resBtn = QMessageBox::question( this, "HusterM",
                                                                        tr("文件已存在,确认覆盖?\n"),
                                                                        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
            if (resBtn != QMessageBox::Yes) {

            } else {
                client->executeShellCommand("rm "+currentPathRemote+"/"+fileInfo.fileName().toStdString(),outputString);
                QFile file(fileInfo.absoluteFilePath());
                if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    fileSize = file.size();
                }
                file.close();

                speedCalculatorThread = new QThread;
                speedWorker = new SpeedCalculator(0,m_configure);
                speedWorker->moveToThread(speedCalculatorThread);
                connect(ftpWorker, SIGNAL(finishUpload()), speedWorker, SLOT(process()));
                //connect start signal to process slot
                connect(this,SIGNAL(uploadSpeedMonitingStart(QString,QString,qint64)),speedWorker,SLOT(processUploadSpeed(QString,QString,qint64)));
                //connect worker  signal to main process slot
                connect(speedWorker,SIGNAL(getUploadSpeedSignal(int,qint64)),this,SLOT(displayUpdateSpeed(int,qint64)));
                //deal with destroy signals
                connect(speedCalculatorThread,SIGNAL(destroyed()),speedWorker,SLOT(process()));
                connect(speedWorker,SIGNAL(finished()),speedCalculatorThread,SLOT(quit()));
                connect(speedWorker,SIGNAL(finished()),speedWorker,SLOT(deleteLater()));
                connect(speedCalculatorThread,SIGNAL(finished()),speedCalculatorThread,SLOT(deleteLater()));
                speedCalculatorThread->start();
                emit ftpUploadStart(fileInfo.absoluteFilePath(),QString::fromStdString(currentPathRemote));
                emit uploadSpeedMonitingStart(QString::fromStdString(currentPathRemote),fileInfo.fileName(),fileSize);
                ui.pushButton_3->setText("上传中...");//close button
                ui.pushButton_3->setEnabled(false);//close button
            }
        }
        else
        {
            QFile file(fileInfo.absoluteFilePath());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                fileSize = file.size();
            }
            file.close();

            speedCalculatorThread = new QThread;
            speedWorker = new SpeedCalculator(0,m_configure);
            speedWorker->moveToThread(speedCalculatorThread);
            connect(ftpWorker, SIGNAL(finishUpload()), speedWorker, SLOT(process()));
            //connect start signal to process slot
            connect(this,SIGNAL(uploadSpeedMonitingStart(QString,QString,qint64)),speedWorker,SLOT(processUploadSpeed(QString,QString,qint64)));
            //connect worker  signal to main process slot
            connect(speedWorker,SIGNAL(getUploadSpeedSignal(int,qint64)),this,SLOT(displayUpdateSpeed(int,qint64)));
            //deal with destroy signals
            connect(speedCalculatorThread,SIGNAL(destroyed()),speedWorker,SLOT(process()));
            connect(speedWorker,SIGNAL(finished()),speedCalculatorThread,SLOT(quit()));
            connect(speedWorker,SIGNAL(finished()),speedWorker,SLOT(deleteLater()));
            connect(speedCalculatorThread,SIGNAL(finished()),speedCalculatorThread,SLOT(deleteLater()));
            speedCalculatorThread->start();
            emit ftpUploadStart(fileInfo.absoluteFilePath(),QString::fromStdString(currentPathRemote));
            emit uploadSpeedMonitingStart(QString::fromStdString(currentPathRemote),fileInfo.fileName(),fileSize);
            ui.pushButton_3->setText("上传中...");//close button
            ui.pushButton_3->setEnabled(false);//close button

        }

    }

}


//show text in job view
void MainWindow::on_pushButton_modify_clicked()
{
    client->executeShellCommand("cat "+currentPathRemote+"/"+(ui.treeWidget_job_file->currentItem()->text(0).toStdString()),outputString);
    ui.textBrowser_job_submit_show_2->setPlainText(QString::fromStdString(outputString));

}


//save changes in job view
void MainWindow::on_pushButton_save_clicked()
{
    script=ui.textBrowser_job_submit_show_2->toPlainText();
    QFile file(ui.treeWidget_job_file->currentItem()->text(0));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate))
    {
        QTextStream out(&file);
        out << script;
    }
    rmFileCommand=("rm "+ui.treeWidget_job_file->currentItem()->text(0)).toLatin1().data();
    client->executeShellCommand("rm "+currentPathRemote+"/"+(ui.treeWidget_job_file->currentItem()->text(0).toStdString()),outputString);
    client->putFile(ui.treeWidget_job_file->currentItem()->text(0).toStdString(),currentPathRemote);


    client->executeShellCommand("dos2unix "+currentPathRemote+"/"+ui.treeWidget_job_file->currentItem()->text(0).toStdString(),outputString);
}


//kill a job in monitor tab
void MainWindow::on_pushButton_monitor_job_del_clicked()
{
    int length;length=ui.treeWidget_monitor_jobs->selectedItems().count();
    QString jobName_del;
    if(length>0){
        for(int i=0;i<length;i++){

            jobName_del=ui.treeWidget_monitor_jobs->selectedItems().at(i)->text(0);
            QRegularExpression re("^\\d+");
            QRegularExpressionMatch match = re.match(jobName_del);
            if(match.hasMatch()){

                jobDelCommand=("qdel "+match.captured(0)).toLatin1().data();
                client->executeShellCommand(jobDelCommand,outputString);
            }

        }

    }
}


//refresh joblist in job monitor tab
void MainWindow::on_pushButton_monitor_job_refresh_clicked()
{
    //reset list
    ui.treeWidget_monitor_jobs->clear();
    inputString = getJobListCmd;//get joblist
    client->executeShellCommand(inputString, outputString);
    QStringList jobsList;//declare storage
    QString nodesString;
    QRegularExpression re("(?<=Nodes:\\n)[\\W\\w]*(?=IWD)");
    if(!outputString.empty())
        jobsList=QString::fromStdString(outputString).split("\n");//store job string as string list


    if(outputString!=""){//iterate job stringlist
        for(int i=5;i<jobsList.size()-1;i++){
            //get nodes list
            client->executeShellCommand("checkjobs "+jobsList[i].split(QRegExp("[\\s]+"))[0].split(".")[0].toStdString(),outputString);

            QRegularExpressionMatch match = re.match(QString::fromStdString(outputString));

            if(match.hasMatch()){
                nodesString=match.captured(0).remove("\n");
            }
            //make job item
            QTreeWidgetItem *job = new QTreeWidgetItem(ui.treeWidget_monitor_jobs);
            job->setText(0,jobsList[i].split(QRegExp("[\\s]+"))[0]);//jobID
            job->setText(1,jobsList[i].split(QRegExp("[\\s]+"))[1]);//user
            job->setText(2,jobsList[i].split(QRegExp("[\\s]+"))[2]);//queue
            job->setText(3,jobsList[i].split(QRegExp("[\\s]+"))[3]);//jobName
            job->setText(4,jobsList[i].split(QRegExp("[\\s]+"))[5]+" "+nodesString);//nodes
            job->setText(5,jobsList[i].split(QRegExp("[\\s]+"))[6]);//cores
            job->setText(6,jobsList[i].split(QRegExp("[\\s]+"))[10]);//time
            job->setText(7,jobsList[i].split(QRegExp("[\\s]+"))[9]);//state

            if(jobsList[i].split(QRegExp("[\\s]+"))[9].compare("R")==0)//set running job state as green
                job->setTextColor(7,Qt::green);
            if(jobsList[i].split(QRegExp("[\\s]+"))[9].compare("Q")==0)//set queue job state as red
                job->setTextColor(7,Qt::red);

            ui.treeWidget_monitor_jobs->addTopLevelItem(job);//add to treewidget
        }

    }
}



//make qsub command with existed script
void MainWindow::on_pushButton_job_submit_edit_clicked()
{
    //display existed script
    client->executeShellCommand("cat "+cachePathRemote,outputString);
    ui.textBrowser_job_submit_show->setPlainText(QString::fromStdString(outputString));
    //make qsub command
    //choose submit mode 1
    if(ui.radioButton_parameter_by_nodenum->isChecked()){
        //get script varables
        nodesNum = QString::number(ui.spinBox_nodeNum->value());
        coreNum = QString::number(ui.spinBox_coreNum->value());
        jobName = ui.lineEdit_job_name->text();
        queueName = ui.comboBox_queue->currentText();
        outputLog = ui.lineEdit_job_submit_logname->text();
        //get script name
        QString sName = ui.treeWidget_jobsubmitfile->currentItem()->text(0);

        //make qsub command of mode 1


        //generate qsub command string
        QString qstr = "qsub "+QString::fromStdString(cachePathRemote)+" -l nodes="+nodesNum+":ppn="+coreNum+" -N "+jobName;

        //display qsub command
        ui.textBrowser_job_qsubCommand->setPlainText(qstr);
        //convert qsub command to const char *
        jobSubCommand_seletedScript = qstr.toStdString().c_str();


    }
    //choose submit mode 2
    else if(ui.radioButton_parameter_byNodeName->isChecked()){

        QString qstr2 = ui.lineEdit_jobsubmit_nodesList->text();
        jobName = ui.lineEdit_jobsubmit_taskname2->text();
        queueName = ui.comboBox_queue->currentText();
        outputLog = ui.lineEdit_job_submit_logname->text();
        //get script name
        QString sName = ui.treeWidget_jobsubmitfile->currentItem()->text(0);

        qstr2.replace(":",":ppn=");
        //generate qsub command string
        QString qstr = "qsub "+QString::fromStdString(cachePathRemote)+" -l nodes="+qstr2+" -N "+jobName;

        //display qsub command
        ui.textBrowser_job_qsubCommand->setPlainText(qstr);
        //convert qsub command to const char *
        jobSubCommand_seletedScript = qstr.toStdString().c_str();




    }

}

//display selected script name on label
void MainWindow::on_pushButton_job_submit_selectRemote_clicked()
{
    if(temp_ptr != nullptr)
    {
        temp_ptr->setBackground(0,Qt::white);
    }

    ui.label_job_submit_selectedScript->setText("已选择脚本:"+ui.treeWidget_jobsubmitfile->currentItem()->text(0));
    ui.label_job_submit_selectedScript->setStyleSheet("color:red;");
    QList<QTreeWidgetItem*> items = ui.treeWidget_jobsubmitfile->selectedItems();
    foreach(QTreeWidgetItem* each,items)
    {
        each->setBackground(0,Qt::red);
        temp_ptr = each;
    }
    cachePathRemote = currentPathRemote+"/"+ui.treeWidget_jobsubmitfile->currentItem()->text(0).toStdString();
    on_pushButton_job_submit_edit_clicked();

}


void MainWindow::changeUserSlot(){
    //    emit changeUserSignal();
    //    closeSshClientSession();
    //    closeThreads();
    //    this->hide();
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());

}

//invoke menu when right click
void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("新建文件夹")),this,SLOT(mkRemoteDir()));//add action refresh
    menu->addAction(QString(tr("刷新")),this,SLOT(ftpRefreshList()));//add action refresh
    menu->addAction(QString(tr("删除")),this,SLOT(ftpDeleteFile()));//add action delete
    menu->exec(QCursor::pos());//execute selected action
}

void MainWindow::mkRemoteDir(){
    QString dirName = QInputDialog::getText(this,
                                            tr("新建文件夹"),
                                            tr("文件夹名称"));
    if (!dirName.isEmpty()) {

        emit ftpMkDirStart(QString::fromStdString(currentPathRemote),dirName);


    }
}

//delete selected files
void MainWindow::ftpDeleteFile(){
    //get selected rows
    QModelIndexList indexList = ui.treeWidget->selectionModel()->selectedRows(0);
    QString filename;//store file name for delection
    int indexCount = indexList.count();//get all selected items count
    for(int i =0;i<indexCount;i++){//iterate selected rows
        filename = indexList.at(i).data().toString();//store fileName
        client->executeShellCommand("rm "+currentPathRemote+"/"+filename.toStdString(),outputString);//rm file by name
    }
    ftpRefreshList();
}

void MainWindow::ftpRefreshList(){
    //renew display
    ui.treeWidget->clear();
    updateFileList(ui.treeWidget,3);
}

void MainWindow::on_treeWidget_jobsubmitfile_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("刷新")),this,SLOT(jobSubFileRefreshList()));//add action refresh
    menu->exec(QCursor::pos());//execute selected action
}

void MainWindow::jobSubFileRefreshList(){
    //renew display
    ui.treeWidget_jobsubmitfile->clear();
    updateFileList(ui.treeWidget_jobsubmitfile,1);
}

void MainWindow::on_treeWidget_job_file_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("刷新")),this,SLOT(jobFileViewRefreshList()));//add action refresh
    menu->exec(QCursor::pos());//execute selected action
}
void MainWindow::jobFileViewRefreshList(){
    //renew display
    ui.treeWidget_job_file->clear();
    //get remote dir
    updateFileList(ui.treeWidget_job_file,2);
}

void MainWindow::updateFileList(QTreeWidget* _treeWidget,int widgetIndex){
    int _widgetIndex =widgetIndex;

    //get remote dir
    emit ftpListDirStart(QString::fromStdString(currentPathRemote),_widgetIndex);

}

//enter son directory when double clicked
void MainWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    //get file name
    if(item->isDisabled())return;
    QString name = item->text(0);

    //set currentpathremote if file is directory
    if(isDir(name)){
        currentPathRemote+="/";
        currentPathRemote+=name.toStdString();
        ui.pushButton_cdToParentDir->setEnabled(true);
    }
    //display file list
    updateFileList(ui.treeWidget,3);
    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget_job_file,2);


    //reset current path label
    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));



}

bool MainWindow::isDir(QString name){

    //find out if file is a directory
    //get all file list in current remote path
    SftpDirAttributes attr;
    client->listDir(currentPathRemote,attr);
    //find same file name type
    for(unsigned int i =0;i<attr.size();i++){//iterate file list
        if(QString::fromStdString(attr[i].name).compare(name)==0){
            if(QString::number(attr[i].type).compare("1")==0)
            {
                return false;
            }
            else if (QString::number(attr[i].type).compare("1")!=0)
            {
                return true;
            }


        }

    }return false;
}

void MainWindow::on_pushButton_cdToParentDir_clicked()
{
    //reset curentpathremote
    QString path = QString::fromStdString(currentPathRemote);
    path = path.left(path.lastIndexOf('/'));
    if(path.isEmpty()){
        ui.pushButton_cdToParentDir->setEnabled(false);
        currentPathRemote = "/";

        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_jobsubmitfile,1);
        updateFileList(ui.treeWidget_job_file,2);
        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }
    else{
        currentPathRemote = path.toStdString();

        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_jobsubmitfile,1);
        updateFileList(ui.treeWidget_job_file,2);
        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }

    //show file list
}


void MainWindow::closeEvent (QCloseEvent *event)
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

void MainWindow::on_treeWidget_jobsubmitfile_itemActivated(QTreeWidgetItem *item, int column)
{
    //get file name
    if(item->isDisabled())return;
    QString name = item->text(0);

    //set currentpathremote if file is directory
    if(isDir(name)){
        currentPathRemote+="/";
        currentPathRemote+=name.toStdString();
        ui.pushButton_cdToParentDir_a->setEnabled(true);
    }

    //display file list
    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget_job_file,2);
    updateFileList(ui.treeWidget,3);

    //reset current path label
    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));


}

void MainWindow::on_pushButton_cdToParentDir_a_clicked()
{
    //reset curentpathremote
    QString path = QString::fromStdString(currentPathRemote);
    path = path.left(path.lastIndexOf('/'));
    if(path.isEmpty()){
        ui.pushButton_cdToParentDir->setEnabled(false);
        currentPathRemote = "/";

        updateFileList(ui.treeWidget_jobsubmitfile,1);
        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_job_file,2);
        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }
    else{
        currentPathRemote = path.toStdString();

        updateFileList(ui.treeWidget_jobsubmitfile,1);
        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_job_file,2);
        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }

    //show file list

}


//cpu
void MainWindow::updateCPUGUI(QString output){
    if(status_increment_indicator<65536)
        status_increment_indicator++;
    else
        status_increment_indicator=0;
    ui.widget_cpubar->setValue(output.toFloat());


}

void MainWindow::updateHostTempGUI(int t)
{
    ui.label_host_temprature->setText(QString::number(t));
    if(t>70)
    {
        ui.label_host_temprature->setStyleSheet("color: rgb(255, 0, 0);");
        if(update_flag_s1 == true)
        {
            updateEventMessage(ALERT,"control node","管理节点cpu温度过高！");
            ui.pushButton_temprature->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");

        }

    }
    else
        ui.label_host_temprature->setStyleSheet("color: rgb(0, 255, 0)");

}
//ram
void MainWindow::updateRAMGUI(QString output){
    ui.widget_rambar->setValue(output.toFloat());

}
//disk
void MainWindow::updateDISKGUI(QString output){


    storageInfoList.clear();//reset widget
    //extract useful data
    QRegularExpression re("\\b\\d+.*");
    QRegularExpressionMatchIterator i = re.globalMatch(output);
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();
        QString storageInfo = match.captured(0);
        storageInfoList<<storageInfo;

    }


    for(int i =0;i<storageInfoList.size();i++){
        if(storageInfoList[i].split(QRegExp("[\\s]+")).size()>=5)
        {
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow1_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow1_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_distShowRow1_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
            }
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/boot",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow2_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow2_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_diskShowRow2_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
            }
            if(QString::compare(storageInfoList[i].split(QRegExp("[\\s]+"))[4],"/home",Qt::CaseInsensitive)==0){
                ui.label_usedShowRow3_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[1]);
                ui.label_sizeShowRow3_4->setText(storageInfoList[i].split(QRegExp("[\\s]+"))[0]);
                ui.progressBar_diskShowRow3_4->setValue(storageInfoList[i].split(QRegExp("[\\s]+"))[3].replace("%","").toInt());
            }
        }
    }






}
//date
void MainWindow::updateDATEGUI(QString output){

}
//uptime
void MainWindow::updateUPTIMEGUI(QString output){

    QStringList strList = output.split("/");
    if(strList.size()>=3)
    {
        ui.label_RDay->setText(strList[0]);
        ui.label_RHour->setText(strList[1]);
        ui.label_RMin->setText(strList[2]);
    }


}
//nodes
void MainWindow::updateNODESGUI(QString output){
    nodesList.clear();
    if(output!=""){
        //store nodes info big string as qstring
        nodesinfos = output;
        //iterate all nodes
        for(int i=0;i<nodesinfos.split("\n\n").size();i++)
        {
            //store item in list of stringlist
            nodesList.append(nodesinfos.split("\n\n")[i].split(QRegExp("\\n[\\s]+")));
        }


        //initilizing nodes counters
        isFree = true;
        usedCore=0;
        availableCore=0;
        totalCore=0;
        freeNodes=0;
        partUsedNodes=0;
        fullUsedNodes=0;
        downNodes=0;
        ui.treeWidget_monitor_nodes->clear();//clear the display

        //iterate all nodes for moniter tab display
        for (int i = 0 ;i<nodesList.size()-1;i++)
        {
            QTreeWidgetItem *nodeItem = new QTreeWidgetItem(ui.treeWidget_monitor_nodes);
            nodeItem->setText(0,nodesList[i][0]);
            for(int j=0;j<nodesList[i].size()-1;j++)
            {
                if(nodesList[i][j].split(" = ")[0].compare("np")==0){
                    totalCore = nodesList[i][j].split(" = ")[1].toInt();
                    //                    break;
                }
            }

            for(int j=0;j<nodesList[i].size()-1;j++)
            {
                if(nodesList[i][j].split(" = ")[0].compare("jobs")==1){
                    isFree = false;
                    //                    break;
                }
            }

            if(isFree==true){
                //wei 0
                usedCore = 0;
                availableCore = totalCore -usedCore;
                nodeItem->setText(3,QString::number(usedCore));
                nodeItem->setText(4,QString::number(availableCore));
                nodeItem->setTextColor(0,Qt::green);
                nodeItem->setTextColor(4,Qt::green);
            }

            //iterate all items of a node
            for(int j=0;j<nodesList[i].size()-1;j++){
                //identify busy nodes
                if(nodesList[i][j].split(" = ")[0].compare("jobs")==0){
                    usedCore = nodesList[i][j].split(" = ")[1].split(",").size();//get used cores count
                    availableCore = totalCore -usedCore;//calculate avaliable cores count
                    nodeItem->setText(3,QString::number(usedCore));//show counts
                    nodeItem->setText(4,QString::number(availableCore));
                    if(availableCore==0){
                        nodeItem->setTextColor(0,Qt::red);
                        nodeItem->setTextColor(3,Qt::red);
                        nodeItem->setTextColor(4,Qt::red);
                        fullUsedNodes++;
                    }
                    if(availableCore!=0){
                        nodeItem->setTextColor(0,Qt::blue);
                        nodeItem->setTextColor(3,Qt::red);
                        nodeItem->setTextColor(4,Qt::green);
                        partUsedNodes++;
                    }
                    //                    break;
                }
            }


        }

        //set counters display
        ui.label_freenodes->setText(QString::number(nodesList.size()-partUsedNodes-fullUsedNodes-1));
        ui.label_partusednodes->setText(QString::number(partUsedNodes));
        ui.label_fullusednodes->setText(QString::number(fullUsedNodes));

        ui.label_MainServerCount->setText(QString::number(nodesList.size()-1));
        ui.label_NodeCount_up->setText(QString::number(nodesList.size()-partUsedNodes-fullUsedNodes-1));
        ui.label_NodeCount_down->setText(QString::number(partUsedNodes));

        //iterate all nodes for control tab display
        ui.listWidget_control_nodes->clear();
        downNodes=0;
        for (int i = 0 ;i<nodesList.size()-1;i++){
            QListWidgetItem *nodeItem = new QListWidgetItem(ui.listWidget_control_nodes);
            if(nodesList[i].size()>1)
            {
                nodeItem->setText(nodesList[i][0]);
                if(nodesList[i][1].split(" = ")[1]=="free")
                {
                    nodeItem->setBackgroundColor("#A6FFA6");
                }

                else if(nodesList[i][1].split(" = ")[1]=="down")
                {


                    nodeItem->setBackgroundColor("#FF5809");
                    if(update_flag_s2 == true)
                    {
                        updateEventMessage(ERR,nodesList[i][0],"节点无响应");
                        //                        update_flag_s2 = false;

                    }
//                    ui.label_3->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");
                    ui.pushButton_error->setStyleSheet("background-image: url(:/Resources/redbutton.png);color: rgb(255, 255, 255);border:0px;");
                    downNodes++;
                }
                else
                {
                    nodeItem->setBackgroundColor("#97CBFF");

                }
                //                if(nodesList[i][1].split(" = ")[1].compare("down")==0){

                //                }
            }

        }
        update_flag_s2 = false;

        ui.label_NodeCount_red->setText(QString::number(downNodes));
        ui.label_downnodes->setText(QString::number(downNodes));
        ui.label_NodeCount_down->setText(QString::number(partUsedNodes+fullUsedNodes));

    }
}
//jobs by qstat
void MainWindow::updateJOBSGUI1(QStringList jobList,QStringList nodeList){


    QStringList m_jobsList=jobList;//declare storage
    QStringList m_nodeList=nodeList;
    ui.treeWidget_job_kill->clear();

    for(int i=0;i<m_jobsList.size();i++){

        QTreeWidgetItem *job = new QTreeWidgetItem(ui.treeWidget_job_kill);
        if(m_jobsList[i].split(QRegExp("[\\s]+")).size()>10){
            job->setText(0,m_jobsList[i].split(QRegExp("[\\s]+"))[0]);//jobID
            job->setText(1,m_jobsList[i].split(QRegExp("[\\s]+"))[1]);//user
            if(m_jobsList[i].split(QRegExp("[\\s]+"))[1].compare(QString::fromStdString(m_configure.user))==0)
                job->setTextColor(1,Qt::red); //set user as red
            job->setText(2,m_jobsList[i].split(QRegExp("[\\s]+"))[2]);//queue
            job->setText(3,m_jobsList[i].split(QRegExp("[\\s]+"))[3]);//jobName
            job->setText(4,m_jobsList[i].split(QRegExp("[\\s]+"))[5]+" "+m_nodeList[i]);//nodes
            job->setText(5,m_jobsList[i].split(QRegExp("[\\s]+"))[6]);//cores
            job->setText(6,m_jobsList[i].split(QRegExp("[\\s]+"))[10]);//time
            job->setText(7,m_jobsList[i].split(QRegExp("[\\s]+"))[9]);//state

            if(m_jobsList[i].split(QRegExp("[\\s]+"))[9].compare("R")==0)//set running job state as green
            {
                job->setTextColor(7,Qt::green);
            }
            if(m_jobsList[i].split(QRegExp("[\\s]+"))[9].compare("Q")==0)//set queue job state as red
            {

                job->setTextColor(7,Qt::red);
            }

            ui.treeWidget_monitor_jobs->addTopLevelItem(job);//add to treewidget


        }
        else
        {
            //            static QMessageBox msg;
            //            msg.setText("网络错误");
            //            msg.exec();
        }

    }

}
//jobs by showjobs
void MainWindow::updateJOBSGUI2(QStringList jobList,QStringList nodeList){
    int runningJobs=0;
    int queueingJobs=0;

    QStringList m_jobsList=jobList;//declare storage
    QStringList m_nodeList=nodeList;
    ui.treeWidget_monitor_jobs->clear();

    for(int i=0;i<m_jobsList.size();i++){

        QTreeWidgetItem *job = new QTreeWidgetItem(ui.treeWidget_monitor_jobs);
        if(m_jobsList[i].split(QRegExp("[\\s]+")).size()>10){
            job->setText(0,m_jobsList[i].split(QRegExp("[\\s]+"))[0]);//jobID
            job->setText(1,m_jobsList[i].split(QRegExp("[\\s]+"))[1]);//user
            job->setText(2,m_jobsList[i].split(QRegExp("[\\s]+"))[2]);//queue
            job->setText(3,m_jobsList[i].split(QRegExp("[\\s]+"))[3]);//jobName
            job->setText(4,m_jobsList[i].split(QRegExp("[\\s]+"))[5]+" "+m_nodeList[i]);//nodes
            job->setText(5,m_jobsList[i].split(QRegExp("[\\s]+"))[6]);//cores
            job->setText(6,m_jobsList[i].split(QRegExp("[\\s]+"))[10]);//time
            job->setText(7,m_jobsList[i].split(QRegExp("[\\s]+"))[9]);//state

            if(m_jobsList[i].split(QRegExp("[\\s]+"))[9].compare("R")==0)//set running job state as green
            {
                job->setTextColor(7,Qt::green);
                runningJobs++;
            }
            if(m_jobsList[i].split(QRegExp("[\\s]+"))[9].compare("Q")==0)//set queue job state as red
            {

                job->setTextColor(7,Qt::red);
                queueingJobs++;
            }

            ui.treeWidget_monitor_jobs->addTopLevelItem(job);//add to treewidget
            ui.label_jobRunningCount->setText(QString::number(runningJobs));
            ui.label_jobWaitingCount->setText(QString::number(queueingJobs));

        }
        else
        {
            //            static QMessageBox msg;
            //            msg.setText("网络错误");
            //            msg.exec();
        }

    }

}


void MainWindow::on_pushButton_job_submit_selectLocal_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    ".",
                                                    tr("Scripts (*.pbs)"));
    if(!fileName.isEmpty()){
        client->putFile(fileName.toStdString(),".");
        outputString.clear();
        client->executeShellCommand("cat ./"+fileName.right(fileName.size()-1-fileName.lastIndexOf('/')).toStdString(),outputString);
        ui.textBrowser_job_submit_show->setText(QString::fromStdString(outputString));
        //choose submit mode 1
        if(ui.radioButton_parameter_by_nodenum->isChecked()){
            //get script varables
            nodesNum = QString::number(ui.spinBox_nodeNum->value());
            coreNum = QString::number(ui.spinBox_coreNum->value());
            jobName = ui.lineEdit_job_name->text();
            queueName = ui.comboBox_queue->currentText();
            outputLog = ui.lineEdit_job_submit_logname->text();
            //get script name
            QString sName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
            //make qsub command of mode 1


            //generate qsub command string
            QString qstr = "qsub ./"+sName+" -l nodes="+nodesNum+":ppn="+coreNum+" -N "+jobName;

            //display qsub command
            ui.textBrowser_job_qsubCommand->setPlainText(qstr);
            //convert qsub command to const char *
            jobSubCommand_seletedScript = qstr.toStdString().c_str();


        }
        //choose submit mode 2
        else if(ui.radioButton_parameter_byNodeName->isChecked()){

            QString qstr2 = ui.lineEdit_jobsubmit_nodesList->text();
            jobName = ui.lineEdit_jobsubmit_taskname2->text();
            queueName = ui.comboBox_queue->currentText();
            outputLog = ui.lineEdit_job_submit_logname->text();
            //  walltime = ui.timeEdit_walltime->text()+":00";
            //get script name
            QString sName = fileName.right(fileName.lastIndexOf("\\"));


            //generate qsub command string
            QString qstr = "qsub ./"+sName+" -l nodes="+qstr2+" -N "+jobName;

            //display qsub command
            ui.textBrowser_job_qsubCommand->setPlainText(qstr);
            //convert qsub command to const char *
            jobSubCommand_seletedScript = qstr.toStdString().c_str();


        }
    }

}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch(index){
    case 0:
    {
        ui.label_title->setText("总览");
        break;
    }
    case 1:
    {
        ui.label_title->setText("作业");
        break;
    }
    case 2:
    {
        ui.label_title->setText("监控");
        break;
    }
    case 3:
    {
        ui.label_title->setText("管理");
        break;
    }
    case 4:
    {
        ui.label_title->setText("传输");
        break;
    }
    case 5:
    {
        ui.label_title->setText("终端");
        break;
    }
    case 6:
    {
        ui.label_title->setText("消息");
        break;
    }
    case 7:
    {
        ui.label_title->setText("设备");
        break;
    }
    }
}

void MainWindow::on_treeWidget_job_file_itemActivated(QTreeWidgetItem *item, int column)
{
    if(temp_ptr2 != nullptr)
    {
        temp_ptr2->setBackground(0,Qt::white);
    }


    item->setBackground(0,Qt::red);
    temp_ptr2 = item;

    //get file name
    if(item->isDisabled())return;
    QString name = item->text(0);

    //set currentpathremote if file is directory
    if(isDir(name)){
        currentPathRemote+="/";
        currentPathRemote+=name.toStdString();
        ui.pushButton_cdToParentDir->setEnabled(true);

        //display file list
        updateFileList(ui.treeWidget_job_file,2);
        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_jobsubmitfile,1);


        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));
    }
    else
    {
        client->executeShellCommand("cat "+currentPathRemote+"/"+(item->text(0).toStdString()),outputString);
        ui.textBrowser_job_submit_show_2->setPlainText(QString::fromStdString(outputString));
    }


}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        ui.tabWidget->setCurrentIndex(2);
    }
}


bool MainWindow::event(QEvent *event)
{
    static int currentTabIndex = 0;

    if (event->type() == QEvent::KeyPress) {

        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Tab) {
            currentTabIndex=(ui.tabWidget->currentIndex()+1) % ui.tabWidget->count();
            ui.tabWidget->setCurrentIndex((ui.tabWidget->currentIndex()+1) % ui.tabWidget->count());
            switch(currentTabIndex){
            case 0:
            {
                ui.label_title->setText("总览");
                break;
            }
            case 1:
            {
                ui.label_title->setText("作业");
                break;
            }
            case 2:
            {
                ui.label_title->setText("监控");
                break;
            }
            case 3:
            {
                ui.label_title->setText("管理");
                break;
            }
            case 4:
            {
                ui.label_title->setText("ftp");
                break;
            }
            case 5:
            {
                ui.label_title->setText("终端");
                break;
            }
            case 6:
            {
                ui.label_title->setText("消息");
                break;
            }
            case 7:
            {
                ui.label_title->setText("设备");
                break;
            }
            }
            return true;

        }

    }


    return QWidget::event(event);

}

void MainWindow::on_lineEdit_ftp_remotePath_returnPressed()
{
    currentPathRemote = ui.lineEdit_ftp_remotePath->text().toStdString();

    updateFileList(ui.treeWidget,3);
    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget_job_file,2);
    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

}

void MainWindow::displayUpdateSpeed(int i,qint64 j){

    ui.pushButton_3->setText("上传速度: "+QString::number(i/1024)+"KB/S  上传进度: %"+QString::number(j));
}


void MainWindow::on_pushButton_localFile_reset_clicked()
{
    ui.treeView->reset();
}

void MainWindow::on_pushButton_localFileUp_clicked()
{
    localDir.cd("..");
    ui.lineEdit_ftp_localPath->setText(localDir.absolutePath());
    ui.treeView->setRootIndex(model->index(localDir.absolutePath()));
}

void MainWindow::on_lineEdit_ftp_localPath_returnPressed()
{
    localDir.cd(ui.lineEdit_ftp_localPath->text());
    ui.treeView->setRootIndex(model->index(localDir.absolutePath()));
}


void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("新建文件")),this,SLOT(mkLocalFile()));
    menu->addAction(QString(tr("新建文件夹")),this,SLOT(mkLocalDir()));
    menu->addAction(QString(tr("重命名")),this,SLOT(reNameLocalFile()));
    menu->addAction(QString(tr("刷新")),this,SLOT(reFreshLocal()));
    menu->addAction(QString(tr("删除")),this,SLOT(deleteLocal()));
    menu->exec(QCursor::pos());//execute selected action
}

void MainWindow::mkLocalFile(){

    QString fileName = QInputDialog::getText(this,
                                             tr("新建文件"),
                                             tr("文件名称"));//get new file name
    QFile file(localDir.absolutePath()+"/"+fileName);//open or create file
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        model->refresh();
    }
    else{
        QMessageBox::information(this,
                                 tr("新建文件"),
                                 tr("创建文件失败"));//show message

    }
}
void MainWindow::mkLocalDir(){
    QString dirName = QInputDialog::getText(this,
                                            tr("新建文件夹"),
                                            tr("文件夹名称"));
    if (!dirName.isEmpty()) {

        if(localDir.mkdir(dirName))
        {
            model->refresh();
        }

        else
        {
            QMessageBox::information(this,
                                     tr("新建文件夹"),
                                     tr("创建文件夹失败"));//show message

        }

    }

}
void MainWindow::reNameLocalFile(){
    QModelIndexList indexList = ui.treeView->selectionModel()->selectedRows(0);

    if(!indexList.isEmpty()){
        QString fileName = QInputDialog::getText(this,
                                                 tr("重命名文件"),
                                                 tr("新文件名称"));//get new file name

        if(!localDir.rename(indexList.at(0).data().toString(),fileName))
        {
            QMessageBox::information(this,
                                     tr("重命名文件"),
                                     tr("创建文件失败"));//show message

        }
        model->refresh();
    }


}
void MainWindow::reFreshLocal(){
    model->refresh();

}
void MainWindow::deleteLocal(){
    QModelIndexList indexList = ui.treeView->selectionModel()->selectedRows(0);
    int indexCount = indexList.count();//get all selected items count
    for(int i =0;i<indexCount;i++){//iterate selected rows

        if(model->isDir(indexList.at(i)))
            model->rmdir(indexList.at(i));
        else
            model->remove(indexList.at(i));
    }

}


void MainWindow::on_lineEdit_job_sub_pathinput_returnPressed()
{
    currentPathRemote = ui.lineEdit_job_sub_pathinput->text().toStdString();

    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget_job_file,2);
    updateFileList(ui.treeWidget,3);

    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    // ui.label_jobSub_fileTree->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));
}

void MainWindow::on_lineEdit_job_file_remotepathinput_returnPressed()
{
    currentPathRemote = ui.lineEdit_job_file_remotepathinput->text().toStdString();


    updateFileList(ui.treeWidget_job_file,2);
    updateFileList(ui.treeWidget_jobsubmitfile,1);
    updateFileList(ui.treeWidget,3);
    ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    // ui.label_jobSub_fileTree->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
    ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
    ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));
}

void MainWindow::on_pushButton_job_file_up_clicked()
{
    //reset curentpathremote
    QString path = QString::fromStdString(currentPathRemote);
    path = path.left(path.lastIndexOf('/'));
    if(path.isEmpty()){
        ui.pushButton_cdToParentDir->setEnabled(false);
        currentPathRemote = "/";

        updateFileList(ui.treeWidget_job_file,2);
        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_jobsubmitfile,1);

        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }
    else{
        currentPathRemote = path.toStdString();

        updateFileList(ui.treeWidget_job_file,2);
        updateFileList(ui.treeWidget,3);
        updateFileList(ui.treeWidget_jobsubmitfile,1);

        ui.lineEdit_ftp_remotePath->setText(QString::fromStdString(currentPathRemote));ui.label_job_submit_currentPath->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_sub_pathinput->setText(QString::fromStdString(currentPathRemote));
        ui.lineEdit_job_file_remotepathinput->setText(QString::fromStdString(currentPathRemote));

    }

    //show file list
}

void MainWindow::on_listWidget_manager_user_view1_itemClicked(QListWidgetItem *item)
{
    QString username = item->text();
    //in .. way to get user info and display by username;
    //label_control_user_view_content_show
    //send user selection signal
    if(!userList.isEmpty())
    {
        foreach(QStringList each, userList)
        {
            if(each[0]==username)
            {
                ui.label_control_user_view_content_show->setText(each[3]);
            }
        }
    }
    emit getQueueOfUserStart(username);
}

void MainWindow::on_pushButton_control_user_add_clicked()
{
    //get user input
    QString userName = ui.lineEdit_control_user_addusername->text();
    QString userGroup = ui.lineEdit_control_user_add_usergroup->text();
    QString passWord;
    if(ui.lineEdit_control_user_adduserpassword->text().compare(ui.lineEdit_control_user_adduserpasswordconfirm->text())==0)
    {
        passWord = ui.lineEdit_control_user_adduserpassword->text();

        //send add user signal
        emit addUserStartSignal(userName,userGroup,passWord);

        //add user to queue if selected
        QList<QListWidgetItem *> seletedQueueItems = ui.listWidget_showLimitedQueues->selectedItems();
        foreach(QListWidgetItem *item,seletedQueueItems)
        {

            client->executeShellCommand("qmgr -c 'set queue "+item->text().toStdString()+" acl_users += "+userName.toStdString()+"'",outputString);

        }
        //synchronize users to compute nodes
        syncronizeUsers( userName, userGroup);

        //refresh userlist
        emit manageGetAllUserStart();
        QMessageBox msg;
        msg.setText("finish adding");
        msg.exec();
    }

    else
    {
        QMessageBox msg;
        msg.setText("密码不一致，重输");
        msg.exec();
    }

    syncronizeUsers(userName,userGroup);
}

void MainWindow::syncronizeUsers(QString userName, QString userGroup)
{
    std::string cmd;
    cmd.append("cd /home/"+userName.toStdString());
    cmd.append(" && mkdir .ssh");
    cmd.append(" && chown "+userName.toStdString()+":"+userGroup.toStdString()+" .ssh");
    cmd.append(" && chmod 700 -R .ssh");

    //scp /etc/passwd  root@comput2:/etc
    //    scp /etc/group     root@comput2:/etc
    //list of a stringlist
    for(int i =0;i<nodesList.size()-1;i++)
    {
        cmd.append(" && scp /etc/passwd root@"+nodesList[i][0].toStdString()+":/etc");
        cmd.append(" && scp /etc/group root@"+nodesList[i][0].toStdString()+":/etc");
        cmd.append(" && scp /etc/shadow root@"+nodesList[i][0].toStdString()+":/etc");

    }
    cmd.append(" && cd .ssh");
    //ssh-keygen -t rsa   //生成 id_rsa 和 id_rsa.pub  （出现提示，回车）
    cmd.append(" && echo -ne '\\n' | su - "+userName.toStdString()+" -c \"ssh-keygen -t rsa\"");

    //cat id_rsa.pub > ~/.ssh/authorized_keys
    // cmd.append(" && su - "+userName.toStdString()+" -c \"cat id_rsa.pub > authorized_keys\"");
    cmd.append(" && cat id_rsa.pub > authorized_keys");
    cmd.append(" && chown "+userName.toStdString()+":"+userGroup.toStdString()+" authorized_keys");
    //chmod 600 ~/.ssh/authorized_keys
    cmd.append(" && chmod 600 authorized_keys");
    cmd.append(" && echo 'StrictHostKeyChecking no' > config");
    cmd.append(" && chown "+userName.toStdString()+":"+userGroup.toStdString()+" config");
    //chmod 600 ~/.ssh/authorized_keys
    // qDebug()<<QString::fromStdString(cmd);
    client->executeShellCommand(cmd,outputString);
    //    cmd.append(" ");
}

void MainWindow::on_pushButton_control_queue_add_clicked()
{
    //get input info
    QueueAttributes attr;
    attr.setName(ui.lineEdit_control_queue_add->text());
    attr.setWalltime(ui.lineEdit_walltime->text());
    attr.setMaxCores(ui.lineEdit_control_queue_maxcores->text());
    attr.setMaxJobs(ui.lineEdit_control_queue_maxtask->text());
    attr.setPriority(ui.lineEdit_level->text());
    attr.setUsableNodesCount(ui.lineEdit_control_queue_maxnode->text());

    if(ui.checkBox_nodes->isChecked())
    {
        attr.setNodes(ui.lineEdit_nodes->text().split("+"));
    }

    if(ui.checkBox_limituser->isChecked())
    {
        attr.setUserLimitation(true);
        attr.setLimitedUsers(ui.lineEdit_limitusers->text().split("+"));

    }

    if(ui.checkBox_limitusergroup->isChecked())
    {
        attr.setGroupLimitation(true);
        attr.setLimitedGroups(ui.lineEdit_limitusergroups->text().split("+"));
    }



    //pass input info to service provider
    emit addQueueStartSignal(attr);
    //    //execute command
    emit refreshStartSignal();
    emit getLimitedQueuesStart();
    emit getAllQueueInfosStart();
    setupQueue();
    QMessageBox msg;
    msg.setText("finish adding");
    msg.exec();
}

void MainWindow::on_tabWidget_control_time_tabBarClicked(int index)
{
    ui.treeWidget_control_time_statics->clear();
    if(index==0)
    {
        //
        TimeUserSelectionDialog *t = new TimeUserSelectionDialog(this,userList);
        connect(t,SIGNAL(finishGetUsersAndTime(QStringList,QString,QString)),this,SLOT(processTimeGetDataFinishEvent(QStringList,QString,QString)));

        t->show();
    }
}

void MainWindow::processTimeGetDataFinishEvent(QStringList users,QString startTime,QString endTime)
{
    QStringList m_users = users;
    QString m_startTime = startTime;
    QString m_endTime = endTime;
    std::string cmd;
    foreach(QString each, m_users)
    {
        cmd = "cd /opt/gridview/pbs/dispatcher/server_priv/accounting && python main.py "+each.toStdString()+" "+m_startTime.replace("/","").toStdString()+" "+m_endTime.replace("/","").toStdString()+"";
        client->executeShellCommand(cmd,outputString);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget_control_time_statics);
        item->setText(0,each);
        item->setText(1,startTime);
        item->setText(2,endTime);

        if(QString::fromStdString(outputString).split("\n").size()>=3)
        {

            item->setText(3,QString::fromStdString(outputString).split("\n")[1]);
            item->setText(4,QString::fromStdString(outputString).split("\n")[2]);
            item->setText(5,QString::fromStdString(outputString).split("\n")[0]);
        }

    }
}

void MainWindow::on_pushButton_restart_clicked()
{
    QList<QListWidgetItem *> items = ui.listWidget_control_nodes->selectedItems();
    foreach(QListWidgetItem* each,items)
    {
        client->executeShellCommand("ssh "+m_configure.user+"@"+each->text().toStdString()+" reboot",outputString);
    }

}

void MainWindow::on_pushButton_control_queue_delete_clicked()
{
    //get queue name
    QString selected_queue;
    QList<QTreeWidgetItem *> item_list = ui.treeWidget_control_queue_view->selectedItems();
    foreach(QTreeWidgetItem * each, item_list)
    {
        selected_queue = each->text(0);

    }
    //store queue name
    //get all nodes with property queue name

    client->executeShellCommand("qmgr -c 'del queue "+selected_queue.toStdString()+"'",outputString);
    emit refreshStartSignal();
    emit getLimitedQueuesStart();
    emit getAllQueueInfosStart();
}

void MainWindow::on_pushButton_shutdown_clicked()
{
    QList<QListWidgetItem *> items = ui.listWidget_control_nodes->selectedItems();
    foreach(QListWidgetItem* each,items)
    {
        client->executeShellCommand("ssh "+m_configure.user+"@"+each->text().toStdString()+" shutdown -h now",outputString);
    }
}

void MainWindow::on_treeWidget_monitor_nodes_itemClicked(QTreeWidgetItem *item, int column)
{

    //    emit getSonNodeInfoStartSignal(item->text(0));

    displaySonNodeInfo(item->text(0));
}

void MainWindow::displaySonNodeInfo(QString hostname)
{
    ui.label_monitor_showNodeSelected->setText(hostname);

    client->executeShellCommand("ssh "+hostname.toStdString()+" \"cat /proc/cpuinfo | grep -m 1 'cpu MHz' && cat /proc/cpuinfo | grep -m 1  'model name' && nproc && cat /proc/loadavg && vmstat -s | grep 'total memory' && free | grep buffers/cache && df -H | grep '/$'\"",outputString);
    qDebug()<<QString::fromStdString(outputString);
    QStringList str_list = QString::fromStdString(outputString).split("\n");
    if(str_list.size()>=7)
    {
        QString cpuType = str_list[1].split("\t: ")[1];
        qDebug()<<cpuType;
        int cpuCores = str_list[2].toInt();qDebug()<<cpuCores;
        QString cpuFreqs = str_list[0].split("\t\t: ")[1];qDebug()<<cpuFreqs;
        double m_cpuUsage = str_list[3].split(" ")[1].toDouble()/cpuCores*100;qDebug()<<m_cpuUsage;
        if(m_cpuUsage>100)
            m_cpuUsage=100;


        ui.label_CPUTypeShow_monitor->setText(cpuType);
        ui.label_CPUCoreShow_monitor->setText(QString::number(cpuCores));
        ui.label_CPUFreqShow_monitor->setText(cpuFreqs);
        ui.CPUprogressBar_monitor->setValue(m_cpuUsage);

        double totalMem = str_list[4].split(QRegExp("[\\s]+"))[1].toDouble()/1024/1024;qDebug()<<str_list[4].split(QRegExp("[\\s]+"))[1].toDouble();qDebug()<<"total";
        double usedMem = str_list[4].split(QRegExp("[\\s]+"))[1].toDouble() - str_list[5].split(QRegExp("[\\s]+"))[3].toDouble();qDebug()<<str_list[5];qDebug()<<"free";
        double memUsage = usedMem / str_list[4].split(QRegExp("[\\s]+"))[1].toDouble() * 100;qDebug()<<memUsage;qDebug()<<"usage";


        ui.label_RamTypeShow_monitor->setText("GDDR");
        ui.label_RamSizeShow_monitor->setText(QString::number(totalMem)+"GB");
        ui.RAMprogressBar_monitor->setValue(memUsage);

        QString usedDisk = str_list[6].split(QRegExp("[\\s]+"))[2];
        QString totalDisk = str_list[6].split(QRegExp("[\\s]+"))[1];
        int diskUsage = str_list[6].split(QRegExp("[\\s]+"))[4].remove("%").toInt();

        ui.label_usedShowRow1_monitor->setText(usedDisk);
        ui.label_sizeShowRow1_monitor->setText(totalDisk);
        ui.progressBar_distShowRow1_monitor->setValue(diskUsage);
    }

}


void MainWindow::on_treeWidget_nodeViewer_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = new QMenu;
    menu->addAction(QString(tr("monitoring")),this,SLOT(monitorSonNode()));
    menu->exec(QCursor::pos());
}

QString MainWindow::getSelectedNode()
{
    QString hostname;//store hostname

    QList<QTreeWidgetItem *> itemList = ui.treeWidget_nodeViewer->selectedItems();//get selected hostname
    foreach(QTreeWidgetItem* each, itemList)
    {
        hostname = each->text(0);

    }
    return hostname;
}

void MainWindow::monitorSonNode()
{
    QString hostname = getSelectedNode();//store hostname

    QThread * nodeHeartBeatUpdatorThread = new QThread; //initilize heartbeat thread
    MonitorWorker *nodeInfoHeartBeatWorker = new MonitorWorker(0,m_configure,hostname); //initilize heartbeat worker
    nodeInfoHeartBeatWorker->moveToThread(nodeHeartBeatUpdatorThread);//move to thread start event loop


    //deal with destroy signals
    connect(nodeHeartBeatUpdatorThread, SIGNAL (destroyed()), nodeInfoHeartBeatWorker, SLOT (process()));
    connect(nodeInfoHeartBeatWorker, SIGNAL (finished()), nodeHeartBeatUpdatorThread, SLOT (quit()));
    connect(nodeInfoHeartBeatWorker, SIGNAL (finished()), nodeInfoHeartBeatWorker, SLOT (deleteLater()));
    connect(nodeHeartBeatUpdatorThread, SIGNAL (finished()), nodeHeartBeatUpdatorThread, SLOT (deleteLater()));
    nodeHeartBeatUpdatorThread->start();//start thread

}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_listWidget_manager_user_view1_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("删除")),this,SLOT(delSystemUser()));//add action user delete
    menu->exec(QCursor::pos());//execute selected action
}

void MainWindow::delSystemUser()
{
    //get selected user name
    std::string userName;
    std::string cmd;
    QList<QListWidgetItem *> items = ui.listWidget_manager_user_view1->selectedItems();
    foreach(QListWidgetItem *each,items)
    {
        userName=each->text().toStdString();
    }
    cmd = "userdel "+userName;
    for(int i =0;i<nodesList.size()-1;i++)
    {
        cmd.append(" && scp /etc/passwd root@"+nodesList[i][0].toStdString()+":/etc");
        cmd.append(" && scp /etc/group root@"+nodesList[i][0].toStdString()+":/etc");
        cmd.append(" && scp /etc/shadow root@"+nodesList[i][0].toStdString()+":/etc");

    }
    cmd.append(" && rm -r /home/"+userName);

    client->executeShellCommand(cmd,outputString);
    emit manageGetAllUserStart();

}

void MainWindow::on_listWidget_nodes_hardware_itemClicked(QListWidgetItem *item)
{
    QList<QListWidgetItem*> items = ui.listWidget_nodes_hardware->selectedItems();
    foreach(QListWidgetItem* each, items)
    {
        activated_node = each->text();
    }
    ui.label_selectedNodes_hardware->setText("节点：\n"+activated_node);
    plotHistoryRangeReset();
}

void MainWindow::on_treeWidget_bottomMessage_customContextMenuRequested(const QPoint &pos)
{
    //create menu
    QMenu* menu = new QMenu;
    menu->addAction(QString(tr("清除所有")),this,SLOT(messageBoxClearSlot()));//add action refresh
    menu->exec(QCursor::pos());//execute selected action
}

void MainWindow::messageBoxClearSlot()
{
    ui.treeWidget_bottomMessage->clear();
}

void MainWindow::on_action_disconnect_triggered()
{


    if(current_state_label_show.text().compare("online")==0)
    {
        //        ui.label_connection_indicator->setText("offline");
        current_state_label_show.setText("offline");
        current_state_label_show.setStyleSheet("color: red;");
        closeSshClientSession();
        closeThreads();
    }

    else
    {
        QMessageBox messageBox;
        messageBox.setText("已断开连接。");
        messageBox.exec();
    }
}

void MainWindow::on_action_connect_triggered()
{
    if(current_state_label_show.text().compare("offline")==0)
    {
        //        ui.label_connection_indicator->setText("online");
        current_state_label_show.setText("online");
        current_state_label_show.setStyleSheet("color:green;");
        reconnect();

    }

    else
    {
        QMessageBox messageBox;
        messageBox.setText("已连接。");
        messageBox.exec();
    }

}

void MainWindow::on_action_ChangeUser_triggered()
{

}

void MainWindow::on_action_changeUser_triggered()
{
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());

}

void MainWindow::on_pushButton_monitor_CPU_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
    ui.pushButton_monitor_CPU->setChecked(true);
    ui.pushButton_monitor_GPU_2->setChecked(false);
    ui.pushButton_monitor_IBCard_2->setChecked(false);
}

void MainWindow::on_pushButton_monitor_GPU_2_clicked()
{

    ui.stackedWidget->setCurrentIndex(1);
    ui.pushButton_monitor_CPU->setChecked(false);
    ui.pushButton_monitor_GPU_2->setChecked(true);
    ui.pushButton_monitor_IBCard_2->setChecked(false);
}

void MainWindow::on_pushButton_monitor_IBCard_2_clicked()
{

    ui.stackedWidget->setCurrentIndex(2);
    ui.pushButton_monitor_CPU->setChecked(false);
    ui.pushButton_monitor_GPU_2->setChecked(false);
    ui.pushButton_monitor_IBCard_2->setChecked(true);
}



void MainWindow::on_pushButton_error_clicked()
{
    update_flag_s2 = true;
}

void MainWindow::on_pushButton_temprature_clicked()
{
    update_flag_s1 = true;
}
