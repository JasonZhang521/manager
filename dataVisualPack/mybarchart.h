#ifndef MYBARCHART_H
#define MYBARCHART_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

class MyBarChart : public QChart
{
    Q_OBJECT
public:
    MyBarChart();
    void setup();
    void updateDisplay(QList<int> usage);
private slots:
    void handleTimeout();
private:
    QList<QBarSet *> m_setList;
    QBarSeries * series;

    QBarSet * bar_ptr;
    QTimer m_timer;
    QList<int> cpuUsage;
    QStringList categories;

    QBarCategoryAxis *axis;
    int i = 0;
};

#endif // MYBARCHART_H
