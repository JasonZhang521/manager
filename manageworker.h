#ifndef MANAGEWORKER_H
#define MANAGEWORKER_H

#include <QObject>
#include <libssh/libssh.h>
#include <SshClient.h>
#include <SshClientSession.h>
#include <SshShellChannel.h>
#include <SshConfigure.h>
#include <QHash>

using namespace SshWrapper;

class QueueAttributes
{
  public:
    QueueAttributes()
  {}
    ~QueueAttributes()
    {}
    private:
      QString m_name;
      QString m_usableNodesCount;
      QString m_maxJobs;
      QString m_maxCores;
      QString m_walltime;
      QString m_priority;
      QStringList m_usableNodesList;

      bool m_isUserLimited=false;
      bool m_isGroupLimited=false;

      QStringList m_limitedUsers;
      QStringList m_limitedGroups;
    public:
      void setLimitedUsers(QStringList u)
      {
          m_limitedUsers=u;
      }

      QStringList getLimitedUsers()
      {
          return m_limitedUsers;
      }

      void setLimitedGroups(QStringList g)
      {
          m_limitedGroups=g;
      }

      QStringList getLimitedGroups()
      {
          return m_limitedGroups;
      }

      void setUserLimitation(bool l)
      {
          m_isUserLimited = l;
      }
      void setGroupLimitation(bool l)
      {
          m_isGroupLimited = l;
      }

      bool isUserLimited()
      {
          return m_isUserLimited;
      }

      bool isGroupLimited()
      {
          return m_isGroupLimited;
      }

      QString getName()
      {
        return m_name;
      }

      void setName(QString s)
      {
        m_name = s;
      }

      void setWalltime(QString s)
      {
        m_walltime = s;
      }

      void setUsableNodesCount(QString s)
      {
          m_usableNodesCount = s;
      }

      void setMaxJobs(QString s)
      {
          m_maxJobs = s;
      }

      void setMaxCores(QString s)
      {
          m_maxCores = s;
      }

      void setPriority(QString s)
      {
          m_priority = s;
      }

      void setNodes(QStringList s_list)
      {
          m_usableNodesList = s_list;
      }

      QString getWalltime()
      {
        return m_walltime;
      }

      QString getUsableNodesCount()
      {
          return m_usableNodesCount;
      }

      QString getMaxJobs()
      {
          return m_maxJobs;
      }

      QString getMaxCores()
      {
          return m_maxCores;
      }

      QString getPriority()
      {
          return m_priority;
      }

      QStringList getNodes()
      {
          return m_usableNodesList;
      }

};
class ManageWorker : public QObject
{
    Q_OBJECT
public:
    explicit ManageWorker(QObject *parent,SshConfigure configure);
    ~ManageWorker();

signals:
  //declare finish signal
  void finished();
  void finishGetAllUser(QList<QStringList> s);
  void finishGetAllQueueName(QStringList s);
  void finishGetQueueInfoByName(QList<QStringList> s);
  void finishGetQueueOfUser(QHash<QString,QList<QStringList>>);
  void finishGetLimitedQueues(QStringList s);

  void finishGetAllQueueInfos(QStringList,QList<QStringList>,QList<QList<QStringList>>);

public slots:
  void process();
  void getAllUser();
  void getAllQueueNameByUser(QString username);
  QList<QStringList> getQueueInfoByName(QString name);
  QStringList getAllQueue();
  void getQueueOfUser(QString username);
  void getLimitedQueues();
  void addUser(QString userName, QString groupName, QString passWord);
  void getAllQueueDetails();
  void addQueue(QueueAttributes attr);
  void refresh();
private:
  SshConfigure configure;
  ssh_session session;
  SshShellChannel *channel;
  SshClientSession *clientSession;
  ISshClient *client;
  std::string outputString;//declare outputString

  QList<QStringList> m_users;//use qstringlist to store user infos

  QList<QStringList> parseUserInfo(std::string outputString);

  QString raw;
  QString getQueueRawData();
  bool isQueueLimited(QString name);
  QString getGroupName(QString uname);



public:
  void test();

};

#endif // MANAGEWORKER_H
