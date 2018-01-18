#ifndef YUNWEI_H
#define YUNWEI_H

#include <QDialog>

namespace Ui {
class YunWei;
}

class YunWei : public QDialog
{
    Q_OBJECT

public:
    explicit YunWei(QWidget *parent = 0);
    ~YunWei();

private slots:
    void on_pushButton_clicked();

private:
    Ui::YunWei *ui;
};

#endif // YUNWEI_H
