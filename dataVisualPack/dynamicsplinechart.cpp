#include "dynamicsplinechart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QtCore/QTime>

DynamicSplineChart::DynamicSplineChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis),
    m_step(0),
    m_x(20),
    m_y(1)
{

//    m_series = 0;
//    m_axis = new QValueAxis;
//    m_step = 0;
//    m_x = 20;
//    m_y =1 ;
    m_series = new QSplineSeries(this);//initilize spline display
    QPen green(Qt::red);//initilize a pen
    green.setWidth(3);//get pen width
    m_series->setPen(green);//set pen
    m_series->append(m_x, m_y);//append point

    addSeries(m_series);//add series to chart
    createDefaultAxes();//initilize axis
    setAxisX(m_axis, m_series);//binding axis
    m_axis->setTickCount(10);//set interval
    axisX()->setRange(0, 20);//set axis range x
    axisY()->setRange(0, 100);//set axis range y

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));//connect timer to updator
    m_timer.setInterval(1000);//set timer interval
    m_timer.start(); // start updating
//    this->setScale(2);
}

DynamicSplineChart::~DynamicSplineChart()
{
}

void DynamicSplineChart::handleTimeout()
{
    qreal x = plotArea().width() / m_axis->tickCount();
    qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    m_x += y;
    m_y = qreal(cpu_usage);
    m_series->append(m_x, m_y);
    scroll(x, 0);
//    if(m_x>50)
//    {
//        m_series->removePoints(0,1);
//    }

//        m_series->clear();
}

void DynamicSplineChart::updateDisplay1(double input)
{
    cpu_usage = input;
}
