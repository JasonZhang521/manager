#ifndef IPCWORKER_H
#define IPCWORKER_H

#include <QObject>
#include "UiClientProcess.h"
#include "ControlNodeBrieflyInfoRequest.h"
#include "ControlNodeBrieflyInfoResponse.h"
#include "ComputerNodeInfoReport.h"
#include "IIpcMessage.h"
#include "Sleep.h"
#include "Trace.h"
#include <memory>

class IPCWorker : public QObject
{
    Q_OBJECT
public:
     IPCWorker(QObject *parent,std::string str);
     ~IPCWorker();


public slots:
   void getMessageOnceSlot();
signals:
void finished();
void sendOneMessageSignal();

public slots:
     void processII();
     void setup(QString);
 private:
 	UiClient::UiClientProcess process;
 	QString hostName_;

    public slots:
 	void update();
};

#endif // IPCWORKER_H
