#include "manageworker.h"
#include <QDebug>
#include <QHash>
#include <QRegularExpression>
#include <QMessageBox>

Q_DECLARE_METATYPE(QList<QStringList>)
Q_DECLARE_METATYPE(QList<QList<QStringList>>)
Q_DECLARE_METATYPE(QueueAttributes)
//Q_DECLARE_METATYPE(QHash<QString,QList<QStringList>>)


ManageWorker::ManageWorker(QObject *parent,SshConfigure configure) : QObject(parent)
{

    qRegisterMetaType<QList<QStringList>>("QList<QStringList>");
    qRegisterMetaType<QList<QList<QStringList>>>("QList<QList<QStringList>>");
    qRegisterMetaType<QHash<QString,QList<QStringList>>>("QHash<QString,QList<QStringList>>");
    qRegisterMetaType<QueueAttributes>("QueueAttributes");

    //create ssh client
    this->configure=configure;
    session = ssh_new();
    channel = new SshShellChannel(session);
    clientSession = new SshClientSession(session, channel, this->configure);
    client = new SshClient(clientSession);
    client->setup();
    client->startShell();
    raw = getQueueRawData();

}
ManageWorker::~ManageWorker()
{
    client->shutdownShell();
    client->shutdown();
    ssh_disconnect(session);
    ssh_free(session);
}

void ManageWorker::process(){
    emit finished();
}

void ManageWorker::getAllUser()
{
    //get user content by shell command
    client->executeShellCommand("gawk -F: '/(home).*(bash$)/{print $1\" \"$3\" \"$4\" \"$6}' /etc/passwd",outputString);
    //store user info as QStringList
    QList<QStringList> t = parseUserInfo(outputString);
    emit finishGetAllUser(t);

}

void ManageWorker::getAllQueueNameByUser(QString username)
{

}

QStringList ManageWorker::getAllQueue()
{
    QStringList temp_queuenames;
    //in ... way to simply get all queue name
    QRegularExpression re("(?<=create queue ).*");
    QRegularExpressionMatchIterator i = re.globalMatch(raw);
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();
        QString queuename = match.captured(0);
        temp_queuenames<<queuename;
    }

    return temp_queuenames;

}

QList<QStringList> ManageWorker::parseUserInfo(std::string outputString)
{
    QStringList qlist;
    QList<QStringList> temp;
    qlist = QString::fromStdString(outputString).split("\n");
    foreach(QString str,  qlist)
    {
        if(!str.isEmpty())
        {
            temp.append(str.split(" "));
        }

    }
    return temp;
}

//input queuename output queue details as hash table
QList<QStringList> ManageWorker::getQueueInfoByName(QString name)
{
    QString name_=name;
    QStringList temp_infos;
    QList<QStringList> output;


    if(!raw.isEmpty())
    {
        QRegularExpression re("(?<=set queue "+name_+" ).*");
        QRegularExpressionMatchIterator i = re.globalMatch(raw);
        while(i.hasNext()){
            QRegularExpressionMatch match = i.next();
            QString data = match.captured(0);
            QStringList temp;
            temp_infos.clear();
            temp=data.split(" ");
            if(temp[1]=="=" || temp[1]=="+=")
            {
                temp_infos.append(temp[0]);
                temp_infos.append(temp[2]);
                output.append(temp_infos);
            }
            // else if(temp[1]=="+=")
            // {
            //   temp_infos.append(temp[0]);
            //   temp_infos.append(temp[2]);
            // }

        }
        return output;
    }

}



QString ManageWorker::getQueueRawData()
{
    outputString.clear();
    client->executeShellCommand("qmgr -c 'p s'",outputString);
    return QString::fromStdString(outputString);
}

void ManageWorker::getQueueOfUser(QString userName)
{
    QString groupName;
    groupName = getGroupName(userName);
    if(userName.contains("@")||groupName.contains("@"))
    {
        QMessageBox msg;
        msg.setText("invalid username or groupname in qmgr queue setting, pls contact developer for help.");
        msg.exec();
    }
    QStringList usableQueues;
    QStringList queues;
    QList<QStringList> queueInfos;
    queues = getAllQueue();
    //identify if there is no limit

    foreach(QString i,queues)
    {
        if(!isQueueLimited(i))
        {
            usableQueues.append(i);
        }
        if(isQueueLimited(i))
        {
            //queue is limited, need to find out if user is valid for this queue
            queueInfos = getQueueInfoByName(i);
            foreach(QStringList s,queueInfos)
            {
                if((s[0]=="acl_users"&&s[1]==userName) || (s[0]=="acl_groups"&&s[1]==groupName)) //add constrain for using simple username
                {
                    usableQueues.append(i);
                    break;
                }
                // if(s[0]=="acl_groups"&&s[1]==groupName)//add constrain for using simple username
                // {
                //   usableQueues.append(i);
                //   break;
                // }
            }
        }

    }
    //find a place to store queueinfos of usableQueues
    QHash<QString,QList<QStringList>> temp;
    foreach(QString each,usableQueues)
    {
        temp.insert(each,getQueueInfoByName(each));    //in ... way to attach queue info to queue list?

    }
    emit finishGetQueueOfUser(temp);


}

bool ManageWorker::isQueueLimited(QString queueName)
{
    //in what way to check if a queue is limited
    //to see if there is acl_users or acl_groups    if has return true if has not return false
    QList<QStringList> queueInfos;
    queueInfos = getQueueInfoByName(queueName);
    foreach(QStringList s,queueInfos)
    {

        if(s[0]=="acl_user_enable"&&s[1]=="True")
        {
            return true;
        }
        else if(s[0]=="acl_group_enable"&&s[1]=="True")
        {
            return true;
        }

    }
    return false;

}

QString ManageWorker::getGroupName(QString name)
{
    outputString.clear();
    client->executeShellCommand("groups "+name.toStdString(),outputString);
    return QString::fromStdString(outputString).split(" : ")[1].remove("\n");
}

//in a ... way to get all infos of an input queue?
void ManageWorker::refresh()
{
    raw = getQueueRawData();
    //
}

void ManageWorker::test()
{
    QueueAttributes attr;
    attr.setName(QString("rescue"));
    attr.setWalltime(QString("3600"));
    addQueue(attr);

}

//expectation: sudo users can add new user freely
void ManageWorker::addUser(QString userName,QString groupName,QString passWord)
{
    QString userName_=userName;
    QString groupName_=groupName;
    QString passWord_=passWord;
    if(!userName_.isEmpty()&&!groupName_.isEmpty()&&!passWord_.isEmpty())
    {
        outputString.clear();
        client->executeShellCommand("groupadd "+groupName_.toStdString(),outputString);
        client->executeShellCommand("useradd -g "+groupName_.toStdString()+" "+userName_.toStdString(),outputString);
        client->executeShellCommand("echo '"+passWord_.toStdString()+"' | passwd --stdin "+userName_.toStdString(),outputString);
    }

}

void ManageWorker::getLimitedQueues()
{
    QStringList queueList;
    QStringList temp_return;
    queueList = getAllQueue();
    foreach(QString queueName,queueList)
    {
        if(isQueueLimited(queueName))
        {
            temp_return.append(queueName);
        }
    }
    //  qDebug()<<temp_return;
    emit finishGetLimitedQueues(temp_return);
}

void ManageWorker::getAllQueueDetails()
{
    QStringList queueList;
    QList<QStringList> queueContentList;
    QList<QList<QStringList>> queuePBSInfo;
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
    }

    foreach(QString each,queueList)
    {
        queuePBSInfo.append(getQueueInfoByName(each));
    }


    emit finishGetAllQueueInfos(queueList,queueContentList,queuePBSInfo);
    //1 raw data parsing//getQueueInfoByName

    //1 p s command details + 2 qstat -q data

    //find out what details are needed

    //emit all queues with details
}

void ManageWorker::addQueue(QueueAttributes attr)
{
    std::string name = attr.getName().toStdString();
    std::string maxJobs = attr.getMaxJobs().toStdString();
    std::string maxCores = attr.getMaxCores().toStdString();
    std::string priority = attr.getPriority().toStdString();
    std::string maxNodes = attr.getUsableNodesCount().toStdString();
    std::string  walltime= attr.getWalltime().toStdString();
    QStringList nodes = attr.getNodes();


    std::string cmd;
    cmd.append("qmgr -c 'create queue "+name+" queue_type=execution'");
    cmd.append(" && qmgr -c 'set queue "+name+" started=true'");
    cmd.append(" && qmgr -c 'set queue "+name+" enabled=true'");
    cmd.append(" && qmgr -c 'set queue "+name+" resources_default.nodes=1'");
    if(!walltime.empty())
        cmd.append(" && qmgr -c 'set queue "+name+" resources_default.walltime="+walltime+"'");
    if(!maxNodes.empty())
        cmd.append(" && qmgr -c 'set queue "+name+" resources_max.nodes="+maxNodes+"'");
    if(!maxCores.empty())
        cmd.append(" && qmgr -c 'set queue "+name+" resources_max.ncpus="+maxCores+"'");
    if(!maxJobs.empty())
        cmd.append(" && qmgr -c 'set queue "+name+" max_queuable="+maxJobs+"'");
    if(!priority.empty())
        cmd.append(" && qmgr -c 'set queue "+name+" priority="+priority+"'");

    //--------------------------------------------
    if(!nodes.isEmpty())
    {
        foreach(QString each,nodes)
        {
            cmd.append(" && qmgr -c 'set node "+each.toStdString()+" properties+="+name+"'");
        }

        cmd.append(" && qmgr -c 'set queue "+name+" resources_default.neednodes = "+name+"'");

    }


    //--------------------------------------------
    if(attr.isUserLimited())
    {
        cmd.append(" && qmgr -c 'set queue "+name+" acl_user_enable = true'");
        foreach(QString each,attr.getLimitedUsers())
        {
            cmd.append(" && qmgr -c 'set queue "+name+" acl_users+="+each.toStdString()+"'");
        }

    }

    if(attr.isGroupLimited())
    {
        cmd.append(" && qmgr -c 'set queue "+name+" acl_group_enable = true'");
        foreach(QString each,attr.getLimitedGroups())
        {
            cmd.append(" && qmgr -c 'set queue "+name+" acl_groups+="+each.toStdString()+"'");
        }
    }

    client->executeShellCommand(cmd,outputString);

}
