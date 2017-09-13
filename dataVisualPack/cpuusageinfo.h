#ifndef CPUUSAGEINFO_H
#define CPUUSAGEINFO_H

#include <QHash>
#include <QObject>

namespace DataVisualPack {

class CpuUsageInfo
{
public:
    CpuUsageInfo();
    int getGeneralUsage() const;
    void setGeneralUsage(int value);

    QList<int> getCoreUsage() const;
    void setCoreUsage(const QList<int> &value);

    QString getCpuType() const;
    void setCpuType(const QString &value);

    QString getCpuFrequency() const;
    void setCpuFrequency(const QString &value);

private:
    int generalUsage;
    QList<int> coreUsage;
    QString cpuType;
    QString cpuFrequency;
};

}

#endif // CPUUSAGEINFO_H
