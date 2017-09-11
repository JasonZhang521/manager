#include "monitorwindow.h"
#include "ui_monitorwindow.h"
#include "dataVisualPack/datacontainer.h"
#include "dataVisualPack/mybarchart.h"
#include <QMouseEvent>
#include <QtCharts/QChartView>
#include <QDebug>
QT_CHARTS_USE_NAMESPACE
MonitorWindow::MonitorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    //--------------------------------------
    {
    m_dynamicChart = new DynamicSplineChart;
    m_dynamicChart->setTitle("General cpu usage");
    m_dynamicChart->legend()->hide();
    m_dynamicChart->setAnimationOptions(QChart::NoAnimation);
    QChartView *chartView = new QChartView(m_dynamicChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *m_layout = new QVBoxLayout(ui->frame_general_cpu);
    m_layout->addWidget(chartView);
    }
    //---------------------------------------

    //---------------------------------------
    {
    m_barChart = new MyBarChart;
    m_barChart->setTitle("core  usage");
    m_barChart->legend()->hide();
    m_barChart->setAnimationOptions(QChart::NoAnimation);
    QChartView *chartView = new QChartView(m_barChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *m_layout = new QVBoxLayout(ui->frame_cores_cpu);
    m_layout->addWidget(chartView);
    }


}

MonitorWindow::~MonitorWindow()
{

    delete ui;
}

void MonitorWindow::updateGUI(DataContainer data)
{
    QList<int> cpuData_ = data.cpuUsage();
    if(cpuData_.size()>0)
    {
        m_dynamicChart->updateDisplay1(double(cpuData_.at(0)));

        m_barChart->updateDisplay(cpuData_);
    }
//    ui->label->setText(data.processUsage());

}

void MonitorWindow::on_pushButton_clicked()
{
    this->canceled_flag = true;
    this->close();
}

void MonitorWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void MonitorWindow::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void MonitorWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}
