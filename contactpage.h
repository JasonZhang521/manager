#ifndef CONTACTPAGE_H
#define CONTACTPAGE_H

#include <QWidget>

namespace Ui {
class ContactPage;
}

class ContactPage : public QWidget
{
    Q_OBJECT

public:
    explicit ContactPage(QWidget *parent = 0);
    ~ContactPage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    QPoint mLastMousePosition;
    bool mMoving;
    Ui::ContactPage *ui;
};

#endif // CONTACTPAGE_H
