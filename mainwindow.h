#ifndef HUNGCLUSTERMANAGER1_H
#define HUNGCLUSTERMANAGER1_H

#include <QApplication>
#include <QtGui>
#include <QTimer>
#include "ftpworker.h"
#include "ui_mainwindow.h"
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QDirModel>
#include <QTreeView>
#include <QFileSystemModel>
#include "libssh/libssh.h"
#include <libssh/sftp.h>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include "shellworker.h"
#include "speedcalculator.h"
#include <QInputDialog>
#include <SftpDirAttribute.h>
#include "manageworker.h"
#include "highlighter.h"
#include "thirdPartyLib/qcustomplot/qcustomplot.h"
#include "ipcworker.h"

#include "ftpdownloaddialog.h"
#include "ftpuploaddialog.h"


//uiclient related headers
#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>
//#include "alphanum.h"



using namespace SshWrapper;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_monitor_node_clicked();
    void on_pushButton_monitor_jobs_clicked();
    void on_pushButton_control_shutdownpage_clicked();
    void on_pushButton_control_userpage_clicked();
    void on_pushButton_control_queuepage_clicked();
    void on_pushButton_control_computingtimepage_clicked();
    void on_pushButton_job_kill_clicked();
    void on_pushButton_job_submit_clicked();
    void on_pushButton_job_file_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_job_submit_makescript_clicked();
    void on_pushButton_job_submit_submit_clicked();
    void on_pushButton_job_kill_refresh_clicked();
    void on_pushButton_job_submit_save_clicked();
    void on_pushButton_job_kill_del_clicked();
    void on_treeView_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_modify_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_monitor_job_del_clicked();
    void on_pushButton_monitor_job_refresh_clicked();

    void on_pushButton_job_submit_edit_clicked();
    void on_pushButton_job_submit_selectRemote_clicked();
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void ftpDeleteFile();
    void ftpRefreshList();
    void on_treeWidget_jobsubmitfile_customContextMenuRequested(const QPoint &pos);

    void jobSubFileRefreshList();
    void on_treeWidget_job_file_customContextMenuRequested(const QPoint &pos);

    void jobFileViewRefreshList();
    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

    void on_pushButton_cdToParentDir_clicked();
    void on_treeWidget_jobsubmitfile_itemActivated(QTreeWidgetItem *item, int column);
    void on_pushButton_cdToParentDir_a_clicked();

    void updateCPUGUI(QString output);
    void updateRAMGUI(QString output);
    void updateDISKGUI(QString output);
    void updateDATEGUI(QString output);
    void updateUPTIMEGUI(QString output);
    void updateNODESGUI(QString output);
    void updateJOBSGUI1(QStringList jobList, QStringList nodeList);
    void updateJOBSGUI2(QStringList jobList, QStringList nodeList);
    void on_pushButton_job_submit_selectLocal_clicked();
    void updateStatusTracer();

    void on_tabWidget_tabBarClicked(int index);
    void on_treeWidget_job_file_itemActivated(QTreeWidgetItem *item, int column);
    void on_lineEdit_ftp_remotePath_returnPressed();
    void displayUpdateSpeed(int i, qint64 j);
    void displayDownloadSpeed(int speed,qint64 percent);
    void on_pushButton_localFile_reset_clicked();
    void on_pushButton_localFileUp_clicked();
    void on_lineEdit_ftp_localPath_returnPressed();

    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void mkLocalFile();
    void mkLocalDir();
    void reNameLocalFile();
    void reFreshLocal();
    void deleteLocal();
    void on_lineEdit_job_sub_pathinput_returnPressed();

    void on_lineEdit_job_file_remotepathinput_returnPressed();

    void on_pushButton_job_file_up_clicked();

    void mkRemoteDir();
    void on_listWidget_manager_user_view1_itemClicked(QListWidgetItem *item);


    void on_pushButton_control_user_add_clicked();
    void on_pushButton_control_queue_add_clicked();

    void on_tabWidget_control_time_tabBarClicked(int index);

    void on_pushButton_restart_clicked();

    void on_pushButton_control_queue_delete_clicked();

    void on_pushButton_shutdown_clicked();

    void on_treeWidget_monitor_nodes_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_nodeViewer_customContextMenuRequested(const QPoint &pos);

    void monitorSonNode();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_listWidget_manager_user_view1_customContextMenuRequested(const QPoint &pos);

    void delSystemUser();
    void updateGetHardwareInfo();
    void on_listWidget_nodes_hardware_itemClicked(QListWidgetItem *item);


    void on_treeWidget_bottomMessage_customContextMenuRequested(const QPoint &pos);

    void messageBoxClearSlot();
    void on_action_disconnect_triggered();

    void on_action_connect_triggered();

    void on_action_ChangeUser_triggered();

    void on_action_changeUser_triggered();

    void updateMessageUpdateTimerFlag();
    void on_pushButton_monitor_CPU_clicked();

    void on_pushButton_monitor_GPU_2_clicked();

    void on_pushButton_monitor_IBCard_2_clicked();

    void on_pushButton_error_clicked();

    void on_pushButton_temprature_clicked();

    void refreshNodesList();

    void on_action_Quit_triggered();

    void on_pushButton_29_clicked();

    void displayCurrentFileSize(qint64 currentSize);
    void displayFullFileSize(qint64 fullFileSize);
public slots:
    void processFtpUploadFinishEvent();//process after upload finished signal
    void processFtpDownloadFinishEvent();//process after recieve download finished signal
    void processFtpListDirFinishEvent(QList<QStringList> qlist, int i);
    void processFtpRemoveFileFinishEvent();
    void processFtpMkDirFinishEvent();
    void processManageGetUserFinishEvent(QList<QStringList> s);
    void processManageGetQueueOfUserFinishEvent(QHash<QString,QList<QStringList>> s);
    void processGetAllQueueInfosFinishEvent(QStringList queueList,QList<QStringList> queueContentList,QList<QList<QStringList>> queuePBSInfos);
    void processGetLimitedQueueFinishEvent(QStringList s);
    void changeUserSlot();
    void processTimeGetDataFinishEvent(QStringList users, QString startTime, QString endTime);
    void processConnectionFailedEvent();
    void processConnectionSuccessEvent();
    void updatePlotHeatBeat();
    void closeSession();
    void updateHostTempGUI(int t);
    void ftpStopGetFile();
    void ftpStopPutFile();
    void displayDownloadSpeed2(int speed, qint64 percent);
    void displayUploadSpeed2(int speed, qint64 percent);
    void displayCurrentFileSizeUp(qint64 currentSize);
private:
    Ui::MainWindow ui;
    void createCircleBar();


    int activated_process_count = 32;
    QLabel current_state_label;
    QLabel current_state_label_show;
    QLabel current_user_label;
    QLabel current_user_label_show;

    QTreeWidgetItem * temp_ptr;
    QTreeWidgetItem * temp_ptr2=nullptr;

    bool update_flag_s1 = true;
    bool update_flag_s2 = true;
    bool update_flag_s3 = true;
    bool update_flag_s4 = true;//for son node temprature
    QTimer* message_update_timer;

    QTimer* double_click_timer;

    Highlighter *highLighter;
    Highlighter *highLighter2;
    QTimer *timer;
    int temp=0;
    int status_increment_indicator=0;
    QDirModel* model;
    QTreeView tree;
    QDir localDir;
    QTreeWidget* currentWidget;

    QProcess *m_process=nullptr;
    QWindow *m_window;
    QVBoxLayout* layout=nullptr;
    QWidget* container;

    FtpDownloadDialog f;

    QString v1,v2,v3,v4,v5;
    QString script;
    QString jobName,queueName,nodesNum,coreNum,walltime,outputLog,errLog,execName;
    QString scriptName;
    int length;

    std::string user, password, hostname;
    SshConfigure m_configure;
    ssh_session session;
    SshShellChannel *channel;
    SshClientSession *clientSession;
    ISshClient *client;
    SftpDirAttributes attrs;

    std::string inputString;
    std::string outputString;//declare outputString
    const char *finalstr;

    std::string currentPathLocal;
    std::string currentPathRemote;
    std::string cachePathRemote;
    QString openTime;
    QString execTime;

    QFileInfo fileInfo;
    QString filePathLocal;

    QVector<double> ticks;
    QVector<double> regenData;

    QString nodesinfos;
    QStringList nodesinfoList;
    QList<QStringList> nodesList;
    QStringList storageInfoList;
    QStringList nodesListForJobSubmition;
    QStringList queueList;
    QList<QStringList> queueContentList;

//    typedef std::map<std::string, int, doj::alphanum_less<std::string> > m_t;
//    m_t m;

    FtpDownloadDialog * m_f;
    FtpUploadDialog * m_fu;

    QThread* ftpThread;//ftp thread
    FtpWorker* ftpWorker;//ftp worker
    QThread* updatorThread;//shell thread
    ShellWorker* shellWorker;//shell worker
    QThread* speedCalculatorThread;//download&upload speed thread
    SpeedCalculator* speedWorker;//speed worker
    QThread* manageThread;
    ManageWorker* manageWorker;

    QString host_cores_freq_cache;
    //declare ipc thread and worker
    QThread* ipcThread;
    IPCWorker* ipcWorker;

    //event type
    enum E_TYPE  {ALERT,EVENT,DISK,RAM,TEMP,MESSAGE,ERR};


    UiClient::UiClientProcess process;
    // static IPCWorker ipcWorker;
    QString activated_node;//node name for hardware display.
    QTimer * timer_hardware_getInfo;
    QList<QStringList> hardware_hostname_list;

    QCPBars *regen;
    QCPBars *rengen2;

    QList<QStringList> userList;

    bool isFree = true;
    int usedCore=0;
    int availableCore=0;
    int totalCore=0;
    int freeNodes=0;
    int partUsedNodes=0;
    int fullUsedNodes=0;
    int downNodes=0;

    int runningjobs;
    int queueingjobs;

    qint64 fileSize;

    QStringList u_queues;//store selected user queueslist

    QVector<double> x,y;
    QVector<double> x1,y1;
    double increamter=1;

    bool isOnline=true;

    float cpuUsage;
    float ramUsage;
    float totalRam=0,usedRam=0;

    const char *jobSubCommand = "qsub temp.pbs";
    const char *jobSubCommand_seletedScript;//store qsub command for selected submition
    const char *rmFileCommand;
    const char *jobDelCommand;
    const char *getJobListCmd = "showjobs";
    const char *getJobListByuser = "qstat -a";
    bool isDir(QString name);
    void updateFileList(QTreeWidget *_treeWidget, int widgetIndex);
    void closeEvent(QCloseEvent *event);
    void setupMenuAction();
    void setupThreads(SshConfigure configure);
    void setupClient(SshConfigure configure);
    void setupMac();
    void setupQueue();
    void setupCurrentpath();
    void setupDateAndUptime();
    void setupHostAndIP();
    void setupStorageDisplay();
    void setupNodesDisplay();
    void setupFtp();
    void setupCPUInfo();
    void setupRamInfo();
    bool hasProperty(QList<QStringList> queuePBSInfos, QString str);
    void setQueuePriority(QTreeWidgetItem *item, int i, QList<QList<QStringList>> queuePBSInfos);
    void setQueueName(QTreeWidgetItem *item, int i, QStringList queueList);
    void setQueueState(QTreeWidgetItem *item, int i, QList<QStringList> queueContentList_);
    void setQueueUsability(QTreeWidgetItem *item, int i, QList<QStringList> queuePBSInfos);
    void syncronizeUsers(QString userName, QString userGroup);
    void setupStatusTracer();

    void  setupStyleSheet();
    void displaySonNodeInfo(QString hostname);
    QString getSelectedNode();
    void setPlotStyle();
    void setupIPCClient(SshConfigure configure);
    void makeHardwareNodesButtons(QList<QStringList> list);
    void updateHardwareGUI(SystemMonitorMessage::ComputerNodeInfoReport *resp);
    void updateCPUTotal(int input);
    void setPlotBackground();
    void setCPUPlotCustomizeStyle();
    void setCpuPlotData(int input);
    void setRamPlotData(int input);
    void setRamPlotCustomizeStyle();

    inline int rangedRand(unsigned int min, unsigned int max){
        return (qrand() % (max-min)+1) + min;
    }
    void setCPUHistoryPlotStyle();
    void updateRamTotal(int input);
    void plotHistoryRangeReset();
    void setRAMHistoryPlotStyle();
    void setupCurrentUser(QString input);
    void updateEventMessage(E_TYPE type, QString node_name, QString message);
    void setupSystemVersion();
    void setupSSHConfigureInfo(SshConfigure configure);
    void closeSshClientSession();
    void closeThreads();
    void reconnect();
    void setupMessageUpdateTimer();
    void getHostCpuFreqCache();
    void executeFtpUpload(QStringList fileName_list, FtpUploadDialog *m_fu);
public:
    void setupSessionConfigure(SshConfigure configure);
signals:
    void ftpDownloadStart(QString filePathRemote,QString filePathLocal);//send ftp download start signal
    void ftpUploadStart(QString filePathLocal,QString filePathRemote);//send ftp upload start signal
    void ftpListDirStart(QString filePathRemote,int i);
    void ftpRemoveFileStart(QString filePathRemote);
    void ftpMkDirStart(QString filePathRemote,QString fileName);
    void changeUserSignal();
    void closedWindow();
    void uploadSpeedMonitingStart(QString,QString,qint64);
    void downloadSpeedMonitingStart(QString,QString,QString);

    void ftpDownloadPauseSignal();
    void ftpDownloadRestartSignal();

    void manageGetAllUserStart();
    void getQueueOfUserStart(QString s);
    void getLimitedQueuesStart();
    void addUserStartSignal(QString s1,QString s2,QString s3);
    void getAllQueueInfosStart();
    void addQueueStartSignal(QueueAttributes attr);
    void refreshStartSignal();

    void startIPCEngineSignal(QString);
    void startGetIPCDataSignal();

protected slots:
    void keyPressEvent(QKeyEvent *event);
    bool event(QEvent *event);
};

#endif // HUNGCLUSTERMANAGER1_H
