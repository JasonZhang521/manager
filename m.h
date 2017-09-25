#ifndef M_H
#define M_H

#include <QMainWindow>

#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>

namespace Ui {
class M;
}

class M : public QMainWindow
{
    Q_OBJECT

public:
    explicit M(QWidget *parent = 0);
    ~M();

private:
    Ui::M *ui;
};

#endif // M_H
