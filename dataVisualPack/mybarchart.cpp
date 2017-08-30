#include "mybarchart.h"
#include <QVBoxLayout>
#include <QDebug>

MyBarChart::MyBarChart()
{
  //mock data
    cpuUsage.append(22);
    cpuUsage.append(22);
    cpuUsage.append(22);
    cpuUsage.append(22);
    cpuUsage.append(22);
    cpuUsage.append(22);
    cpuUsage.append(22);
    setup();
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));//connect timer to updator
    m_timer.setInterval(1000);//set timer interval
    m_timer.start(); // start updating


}

void MyBarChart::setup()
{

    bar_ptr = new QBarSet("test");
    series = new QBarSeries();
    axis = new QBarCategoryAxis();

    if(cpuUsage.size()>=2)
    {
        for(int i =1;i<cpuUsage.size();i++)
        {
          qDebug()<<cpuUsage[i];
            *bar_ptr << cpuUsage[i];
            categories << QString("core")+QString::number(i);
        }
      }
        qDebug()<<categories;

        series->append(bar_ptr);


        addSeries(series);
        setTitle("Simple barchart example");

        axis->append(categories);
        createDefaultAxes();
        setAxisX(axis, series);
        this->legend()->setVisible(true);
        this->legend()->setAlignment(Qt::AlignBottom);//barchart properties

}

void MyBarChart::updateDisplay(QList<int> usage)
{

    // cpuUsage = usage;
    // bar_ptr = new QBarSet("test");
    //
    // if(cpuUsage.size()>=2)
    // {
    //   series->clear();
    //   axis->clear();
    //   categories.clear();
    //     // for(int i =1;i<cpuUsage.size();i++)
    //     // {
    //     //     //
    //     //     *bar_ptr << cpuUsage[i];
    //     //     categories << QString("core")+QString::number(i);
    //     // }
    //     //
    //     // series->append(bar_ptr);
    //     //
    //     //
    //     // addSeries(series);
    //     //
    //     // axis->append(categories);
    //     // createDefaultAxes();
    //     // setAxisX(axis, series);
    // }
}

void MyBarChart::handleTimeout()
{

}
