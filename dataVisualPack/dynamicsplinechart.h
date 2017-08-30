#ifndef DYNAMICSPLINECHART_H
#define DYNAMICSPLINECHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>


QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;//
class QValueAxis;//
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DynamicSplineChart: public QChart
{
    Q_OBJECT
public:
    DynamicSplineChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
   virtual  ~DynamicSplineChart();

public:
    void updateDisplay1(double input);
public slots:
    void handleTimeout();
private:
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axis;
    qreal m_step;
    qreal m_x;
    qreal m_y;

    QTimer m_timer;

    double cpu_usage=0;
};

#endif // DYNAMICSPLINECHART_H
