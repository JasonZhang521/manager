#include "datacontainer.h"

DataContainer::DataContainer()
{

}

QList<int> DataContainer::cpuUsage() const
{
    return m_cpuUsage;
}

void DataContainer::setCpuUsage(const QList<int> &cpuUsage)
{
    m_cpuUsage = cpuUsage;
}

QList<int> DataContainer::ramUsage() const
{
    return m_ramUsage;
}

void DataContainer::setRamUsage(const QList<int> &ramUsage)
{
    m_ramUsage = ramUsage;
}

QList<int> DataContainer::diskUsage() const
{
    return m_diskUsage;
}

void DataContainer::setDiskUsage(const QList<int> &diskUsage)
{
    m_diskUsage = diskUsage;
}

QList<QStringList> DataContainer::processUsage() const
{
    return m_processUsage;
}

void DataContainer::setProcessUsage(const QList<QStringList> &processUsage)
{
    m_processUsage = processUsage;
}
