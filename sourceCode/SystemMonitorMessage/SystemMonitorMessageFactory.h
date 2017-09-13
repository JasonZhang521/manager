#ifndef SYSTEMMONITORMESSAGEFACTORY_H
#define SYSTEMMONITORMESSAGEFACTORY_H
#include "IIpcMessageFactory.h"
#include "Component.h"
#include "Macro.h"

namespace SystemMonitorMessage {
class SystemMonitorMessageFactory : public IpcMessage::IIpcMessageFactory
{
public:
    SystemMonitorMessageFactory();
    virtual ~SystemMonitorMessageFactory();
    virtual IpcMessage::IIpcMessage* createMessage(IpcMessage::IpcMessageApplicationIntType type) const;
public:
    GETCLASSNAME(SystemMonitorMessageFactory)
};
}
#endif // SYSTEMMONITORMESSAGEFACTORY_H
