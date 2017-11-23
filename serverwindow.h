#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <servercreationwindow.h>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private slots:
    void on_action_triggered();

    void processFinished();
    void updateList();
    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actiondelete_triggered();

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_actioncopy_triggered();

private:
    Ui::ServerWindow *ui;
    ServerCreationWindow* c;
    QSettings *m_settings;

signals:
    connectSignal(QString str);
    updateLoginServerWidgetSignal();

};

#endif // SERVERWINDOW_H
