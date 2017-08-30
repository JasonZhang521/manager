#include "monitorworker.h"
#include "dataVisualPack/cpuusageinfo.h"
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>
#include <time.h>

MonitorWorker::MonitorWorker(QObject *parent, SshConfigure configure,QString hostname) : QObject(parent)
  ,m_host(hostname)
{

    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();

    w = new MonitorWindow;
    w->show();
    stoped_flag = false;
    canceled_flag = false;
    started_flag = true;
    QTimer *timer = new QTimer(this);
    timer->singleShot(500,this,SLOT(start()));

}

MonitorWorker::~MonitorWorker()
{
    qDebug()<<"nodeinfo thread killed";
    client->shutdownShell();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

void MonitorWorker::update(QString hostname)
{

    QString out;
    std::string cmd;

    QList<QList<int>> first_cpuUsageInfo;
    QList<QList<int>> second_cpuUsageInfo;
    QList<QList<int>> temp_cpuUsageInfo;
    QList<QList<int>> reduction ;

    QList<int> cpu_usage;
    QList<int> ram_usage;
    QList<int> disk_usage;
    QList<QStringList> process_usage;

    cmd = "ssh "+hostname.toStdString()+ " ";
    cmd += "\"cat /proc/stat | grep cpu";
    cmd += " && echo ------------------------";
    cmd += " && vmstat -s | grep 'total memory'";
    cmd += " && vmstat -s | grep 'used memory'";
    cmd += " && echo ------------------------";
    cmd += " && df | grep '/$'";
    cmd += " && echo ------------------------";//split(" ------------------------ ")
    cmd += " && ps -Ao user,uid,comm,pid,pcpu --sort=-pcpu | head -n "+QString::number(n).toStdString()+"";
    cmd += " && echo ------------------------";
    cmd += " && ps -Ao user,uid,comm,pid,size --sort=-size | head -n "+QString::number(n).toStdString()+"";
    cmd += "\"";

    //cpu, cpu temprature, ramsize , ramtype, ram usage, disksize, diskusage, top cpu consume process, tom
    //ram consume process, netload
    while (!w->canceled_flag && !stoped_flag) {

        /*****************parse cpu**********************/
        reduction.clear();
        cpu_usage.clear();
        first_cpuUsageInfo = temp_cpuUsageInfo;
        client->executeShellCommand(cmd,outputString);
        out = QString::fromStdString(outputString);
        second_cpuUsageInfo=getCpuOneTimeCount(out);//parse cpu
        temp_cpuUsageInfo=second_cpuUsageInfo;
        for(int i =0;i<first_cpuUsageInfo.size();i++)
        {

            QList<int> temp;
            temp.append(second_cpuUsageInfo[i][0]-first_cpuUsageInfo[i][0]);
            temp.append(second_cpuUsageInfo[i][1]-first_cpuUsageInfo[i][1]);

            reduction.append(temp);

        }

        foreach(QList<int> each, reduction)
        {
            cpu_usage.append((double)each[0]/each[1]*100);

        }
        m_dataContainer.setCpuUsage(cpu_usage);
        /****************parse cpu end**********************/

        /****************parse ram***********************/
        ram_usage = getRamUsage(out);
        m_dataContainer.setRamUsage(ram_usage);
        /****************end parse ram********************/

        /****************parse disk *********************/
        disk_usage = getDiskUsage(out);
        m_dataContainer.setDiskUsage(disk_usage);
        /*********************end************************/

        /********************parse processes***************/

        process_usage = getProcesses(out,GETPROCESSBYCPU);
        m_dataContainer.setProcessUsage(process_usage);
        /********************end***************************/


        w->updateGUI(m_dataContainer);
        Delay(1.5*1000);
    }

    if(w->canceled_flag)
    {
        process();
    }

}

QList<QStringList> MonitorWorker::getProcesses(QString input,PS_TYPE type)
{
    QList<QStringList> out;
    QStringList temp_strList;
    QString temp1 = input.split("\n------------------------\n")[3];
    QString temp2 = input.split("\n------------------------\n")[4];
    if(type == GETPROCESSBYCPU)
    {

        temp_strList = temp1.split("\n");
    }

    if(type == GETPROCESSBYMEM)
    {
        temp_strList = temp2.split("\n");
    }

    temp_strList.removeFirst();
    temp_strList.removeLast();
   //split data chunk into pieces by process
    foreach (QString each, temp_strList) {

        out.append(each.split(QRegExp("[\\s]+")));
    }

//prepare every process data

//put every process data into qlist
 return out;
    // return QList of QStringList with process datas
}

QList<int> MonitorWorker::getDiskUsage(QString input)
{
    QList<int> m_diskUsage;
    QString temp = input.split("\n------------------------\n")[2];
    temp=temp.remove("%");
    QStringList temp_list = temp.split(QRegExp("[\\s]+"));
    if(temp_list.size()>=5)
    {
        m_diskUsage.append(temp_list[1].toInt());
        m_diskUsage.append(temp_list[2].toInt());
        m_diskUsage.append(temp_list[3].toInt());
        m_diskUsage.append(temp_list[4].toInt());
    }

    return m_diskUsage;
}

//update cpu gui
//update ram gui
//update disk gui
//update top cpu consuming process
//update top ram consuming process

QList<int> MonitorWorker::getRamUsage(QString input)
{
    QList<int> m_ramUsage;
    QString raw_data = input.split("\n------------------------\n")[1];
    //get raw data
    int total_ram,used_ram;
    int usage_;

    total_ram = raw_data.split("\n")[0].remove(QRegExp("[a-z]+")).remove(QRegExp("[\\s]+")).toInt();
    used_ram = raw_data.split("\n")[1].remove(QRegExp("[a-z]+")).remove(QRegExp("[\\s]+")).toInt();


    //calculate used percentage
    usage_ = (double)used_ram/total_ram*100;
    m_ramUsage.append(used_ram);
    m_ramUsage.append(total_ram);
    m_ramUsage.append(usage_);
    //store used percentage


    return m_ramUsage;//return QList<int>---used ram , total ram, percentage
}

QList<QList<int>> MonitorWorker::getCpuOneTimeCount(QString input)
{
    QList<QList<int>> m_cpuUsageInfo;//
    QList<int> m_cpuUsageInfo1;
    int total_jiffies=0;
    int work_jiffies = 0;
    foreach(QString each,input.split("\n------------------------\n")[0].split("\n"))//each cpu
    {
        total_jiffies=0;
        work_jiffies = 0;
        for(int i = 1;i<=7;i++)
        {
            total_jiffies +=each.split(QRegExp("[\\s]+"))[i].toInt();
            if(i<=3)
                work_jiffies+=each.split(QRegExp("[\\s]+"))[i].toInt();
        }
        QList<int> temp;
        temp.append(work_jiffies);
        temp.append(total_jiffies);
        m_cpuUsageInfo.append(temp);


    }
    return m_cpuUsageInfo;

}

void MonitorWorker::start()
{
    stoped_flag = false;
    canceled_flag = false;
    started_flag = true;
    update(m_host);
}


void MonitorWorker::Delay(int time)//time*1000为秒数
{
    clock_t  now  =  clock();
    while(clock() - now < time);
}

void MonitorWorker::process(){


    qDebug()<<"process() executed";
    emit finished();
}


