#ifndef DATACONTAINER_H
#define DATACONTAINER_H
#include <QObject>

class DataContainer
{
public:
    DataContainer();
    QList<int> cpuUsage() const;
    void setCpuUsage(const QList<int> &cpuUsage);

    QList<int> ramUsage() const;
    void setRamUsage(const QList<int> &ramUsage);

    QList<int> diskUsage() const;
    void setDiskUsage(const QList<int> &diskUsage);

    QList<QStringList> processUsage() const;
    void setProcessUsage(const QList<QStringList> &processUsage);

private:
    QList<int> m_cpuUsage;
    QList<int> m_ramUsage;
    QList<int> m_diskUsage;
    QList<QStringList> m_processUsage;

};

#endif // DATACONTAINER_H
