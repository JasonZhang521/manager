#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include <QWidget>
#include <QObject>
#include "dataVisualPack/dynamicsplinechart.h"
#include "dataVisualPack/mybarchart.h"
#include "dataVisualPack/datacontainer.h"

#include "dataVisualPack/datacontainer.h"
#include <QMouseEvent>
#include <QtCharts/QChartView>
#include <QDebug>

namespace Ui {
class MonitorWindow;
}

class MonitorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWindow(QWidget *parent = 0);
    ~MonitorWindow();

private:
    Ui::MonitorWindow *ui;
    QPoint mLastMousePosition;
    bool mMoving;

    DynamicSplineChart *m_dynamicChart;
    MyBarChart *m_barChart;

public:
    bool canceled_flag=false;
    void updateGUI(DataContainer data);
protected slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();
signals:
   void updateDynamicChartSignal(double);
};

#endif // MONITORWINDOW_H
