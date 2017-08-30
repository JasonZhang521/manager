#ifndef SERVERCREATIONWINDOW_H
#define SERVERCREATIONWINDOW_H

#include <QSettings>
#include <QWidget>

namespace Ui {
class ServerCreationWindow;
}

class ServerCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerCreationWindow(QWidget *parent = 0);
    ~ServerCreationWindow();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ServerCreationWindow *ui;
    QSettings* m_setting;
signals:
    finished();
};

#endif // SERVERCREATIONWINDOW_H
