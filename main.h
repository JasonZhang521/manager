#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QMessageBox>
class MyApplication Q_DECL_FINAL : public QApplication
{
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv) : QApplication(argc, argv) {}

    bool notify(QObject* receiver, QEvent* event) Q_DECL_OVERRIDE
    {
        try {
            return QApplication::notify(receiver, event);
        //} catch (Tango::DevFailed &e) {
            // Handle the desired exception type
        } catch (...) {
            // Handle the rest
            QMessageBox::warning(0,
                                 tr("An unexpected error occurred"),
                                 tr("This is likely a bug."));
        }

         return false;
     }
};
#endif // MAIN_H
