#include "shellworker.h"
#include <QRegularExpression>
#include <QTimer>
#include <QDebug>
#include <time.h>

#define UPDATE_INTERAL 2000

ShellWorker::ShellWorker(QObject *parent, SshConfigure configure) : QObject(parent)
{
    //create ssh client
    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();

    QTimer *timer = new QTimer(this);
    //   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //   timer->start(UPDATE_INTERAL);
    timer->singleShot(UPDATE_INTERAL,this,SLOT(update()));
    // update();



}

ShellWorker::~ShellWorker()
{
    qDebug()<<"thread killed";
    client->shutdownShell();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

void ShellWorker::process(){


    qDebug()<<"process() executed";
    emit finished();
}

void ShellWorker::update(){
    int i =0;
    while(1&&canceled_flag != true){
        client->executeShellCommand("ls /usr",outputString);
        if(QString::fromStdString(outputString).contains("lib64"))
        {
            emit connectionSuccessSignal();
            getHostTemprature();
            getCPU();
            getRAM();
            getDISK();
            getDATE();
            getUPTIME();
            getNODES();
            getJOBS1();
            getJOBS2();
        }
        else
        {

            emit connectionFailedSignal();
            qDebug()<<"connection failed";
            process();
            break;
        }

        Delay(1*1000);


    }
    process();
//    this->deleteLater();


}

//temprature
void ShellWorker::getHostTemprature()
{
    //computer i need you to get host temprature and send this info through signal
    int temprature_Host;
    client->executeShellCommand("cat /sys/class/hwmon/hwmon0/device/temp1_input",outputString);
    temprature_Host = QString::fromStdString(outputString).toInt()/1000;
    emit hostTempratureFinished(temprature_Host);


}

//cpu
void ShellWorker::getCPU(){

    int hostCoreNum;float cpuUsage;float loadavg;
    client->executeShellCommand("nproc",outputString);
    if(outputString!=""){//return is not empty
        hostCoreNum=QString::fromStdString(outputString).remove("\n").toInt();//parse to int of host corenum

    }

    //get load average
    client->executeShellCommand("cat /proc/loadavg | awk '{print $1}'",outputString);
    if(outputString!=""){//return is not empty
        loadavg = QString::fromStdString(outputString).remove("\n").toFloat();//parse to float of loadavg

        if(hostCoreNum!=0)
            cpuUsage = loadavg/hostCoreNum;//calculate cpu usage
        emit cpuFinished(QString::number(cpuUsage*100));
    }


}
//ram
void ShellWorker::getRAM(){

    client->executeShellCommand("free",outputString);float usedRam,totalRam,ramUsage;
    if(outputString!=""){
        QRegularExpression re("\\b\\d.*");
        QRegularExpressionMatch match = re.match(QString::fromStdString(outputString));//get first match of ram info

        if(match.hasMatch()){
            if(match.captured(0).split(QRegExp("[\\s]+")).size()>=2){
                // usedRam = match.captured(0).split(QRegExp("[\\s]+"))[1].toFloat();//get used ram
                totalRam = match.captured(0).split(QRegExp("[\\s]+"))[0].toFloat();//get total ram
            }

        }
      client->executeShellCommand("free | grep buffers/cache | awk '{print $4}'",outputString);
      usedRam =totalRam - QString::fromStdString(outputString).toFloat();
      

        if(totalRam!=0)
            ramUsage = usedRam/totalRam;
        emit ramFinished(QString::number(ramUsage*100));
    }

}
//disk
void ShellWorker::getDISK(){
    client->executeShellCommand("df -h",outputString);//raw data
    if(outputString!=""){
        emit diskFinished(QString::fromStdString(outputString));
    }
}
//date
void ShellWorker::getDATE(){
    client->executeShellCommand("date -d \"$(awk -F. '{print $1}' /proc/uptime) second ago\" +\"%Y-%m-%d %H:%M:%S\"",outputString);
    if(!outputString.empty()){
        emit dateFinished(QString::fromStdString(outputString));
    }
}
//uptime
void ShellWorker::getUPTIME(){
    client->executeShellCommand("cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf(\"%d/%d/%d/%d\",run_days,run_hour,run_minute,run_second)}'",outputString);
    if(outputString!=""){
        emit uptimeFinished(QString::fromStdString(outputString));
    }
}
//nodes
void ShellWorker::getNODES(){
    client->executeShellCommand("pbsnodes",outputString);
    if(outputString!=""){
        emit nodesFinished(QString::fromStdString(outputString));
    }
}
//jobs by qsub
void ShellWorker::getJOBS1(){
    QStringList jobList, nodesList, temp;
    QRegularExpression re("(?<=Nodes:\\n)[\\W\\w]*(?=IWD)");
    jobList.clear();nodesList.clear();temp.clear();
    client->executeShellCommand("qstat -a", outputString);
    jobList = QString::fromStdString(outputString).split("\n");
    if(jobList.size()>=6)
    {
        for(int i=5;i<jobList.size()-1;i++){
            temp.append(jobList[i]);
            client->executeShellCommand("checkjobs "+jobList[i].split(QRegExp("[\\s]+"))[0].split(".")[0].toStdString(),outputString);
            QRegularExpressionMatch match = re.match(QString::fromStdString(outputString));
            if(match.hasMatch()){
                nodesList.append(match.captured(0).remove("\n"));
            }
            else
                nodesList.append("empty nodes");
        }
    }


    if(!temp.isEmpty()&&!nodesList.isEmpty())
        emit jobsQSubFinished(temp,nodesList);


    //    if(outputString!=""){
    //        emit jobsQSubFinished(QString::fromStdString(outputString));
    //    }

}
//jobs by showjobs
void ShellWorker::getJOBS2(){
    QStringList jobList,nodesList,temp;
    QRegularExpression re("(?<=Nodes:\\n)[\\W\\w]*(?=IWD)");
    jobList.clear();nodesList.clear();temp.clear();
    client->executeShellCommand("showjobs", outputString);//get jobstringlist
    jobList = QString::fromStdString(outputString).split("\n");
    if(jobList.size()>=6)
    {
        for(int i=5;i<jobList.size()-1;i++){
            temp.append(jobList[i]);
            client->executeShellCommand("checkjobs "+jobList[i].split(QRegExp("[\\s]+"))[0].split(".")[0].toStdString(),outputString);
            QRegularExpressionMatch match = re.match(QString::fromStdString(outputString));
            if(match.hasMatch()){
                nodesList.append(match.captured(0).remove("\n"));
            }
            else
                nodesList.append("empty nodes");
        }
    }


    if(!temp.isEmpty()&&!nodesList.isEmpty())
        emit jobsShowjobsFinished(temp,nodesList);

}
void ShellWorker::Delay(int time)//time*1000为秒数
{
    clock_t  now  =  clock();
    while(clock() - now < time);
}
