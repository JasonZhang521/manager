#include "speedcalculator.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QTimer>
#include <time.h>
#include <QDebug>
#include <QFile>
#define UPDATE_INTERVAL 3000

SpeedCalculator::SpeedCalculator(QObject *parent, SshConfigure configure) : QObject(parent)
{
    //create ssh client
    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


}

SpeedCalculator::~SpeedCalculator(){
    client->shutdownShell();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

void SpeedCalculator::process(){
    emit finished();
}

void SpeedCalculator::update(){

    static int speed;
    static int temp;

    //update current file size
    temp = currentSize;
    preSize = temp;
    client->executeShellCommand("cd "+filePathRemote_.toStdString()+" && ls -l | awk '$0~/"+fileName_.toStdString()+"/'",outputString);
    if(QString::fromStdString(outputString).split(QRegExp("[\\s]+")).size()>=4)
    {
        currentSize = QString::fromStdString(outputString).split(QRegExp("[\\s]+"))[4].toInt();
        //calculate speed
        speed = (currentSize-preSize)*1000/UPDATE_INTERVAL;
        //        emit getUploadSpeedSignal(speed);

    }


}

void SpeedCalculator::processUploadSpeed(QString filePathRemote,QString fileName,qint64 fullFileSize){
    clock_t begin, end;
    double seconds;
    static int speed;
    static int percentage;
    static qint64 temp;
    preSize=0;
    currentSize=0;
    filePathRemote_=filePathRemote;
    fileName_=fileName;
    //    timer->start(UPDATE_INTERVAL);
    while(1){
        begin = clock();
        Delay(0.4*1000);
        //update current file size
        temp = currentSize;
        preSize = temp;
        client->executeShellCommand("cd "+filePathRemote_.toStdString()+" && ls -l | awk '$0~/"+fileName_.toStdString()+"/'",outputString);
        if(QString::fromStdString(outputString).split(QRegExp("[\\s]+")).size()>=4)
        {
            currentSize = QString::fromStdString(outputString).split(QRegExp("[\\s]+"))[4].toLongLong();
            //calculate speed
            end = clock();
            seconds = (end - begin) / (double)CLOCKS_PER_SEC;
            speed = (currentSize-preSize)/seconds;
            percentage = currentSize*100/fullFileSize;
            emit getUploadSpeedSignal(speed,percentage);



        }
        if(currentSize==fullFileSize)break;


    }
    process();

}

void SpeedCalculator::processDownloadSpeed(QString currentPathRemote,QString localFilePath,QString fileName)
{
    clock_t begin, end, now;
    double seconds;
    static int speed;
    static int percentage;
    static qint64 temp=0;
    preSize=0;
    currentSize=0;
    qint64 fullFileSize =0;

    client->executeShellCommand("cd "+currentPathRemote.toStdString()+" && ls -l | awk '$0~/"+fileName.toStdString()+"/'",outputString);
    if(QString::fromStdString(outputString).split(QRegExp("[\\s]+")).size()>=4)
    {
        fullFileSize = QString::fromStdString(outputString).split(QRegExp("[\\s]+"))[4].toLongLong();
        //calculate speed

    }

    QFile file(localFilePath+"/"+fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

    }
    now = clock();
    while(1)
    {
        begin = clock();
        Delay(0.5*1000);
        temp = currentSize;
        preSize = temp;
        currentSize = file.size();
        end = clock();
        seconds = (end - begin) / (double)CLOCKS_PER_SEC;
        speed = (currentSize-preSize)/seconds;
        percentage = currentSize*100/fullFileSize;
        emit getDownloadSpeedSignal(speed,percentage);
        if(currentSize==fullFileSize)break;

    }


    process();
}
void SpeedCalculator::Delay(int time)//time*1000为秒数
{
    clock_t  now  =  clock();
    while(clock() - now < time);
}

void SpeedCalculator::go(){}
