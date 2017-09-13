#ifndef _SYSTEMMONITOR_SYSTEMINFOCOLLECTOR_H_
#define _SYSTEMMONITOR_SYSTEMINFOCOLLECTOR_H_
#include "IEvent.h"
#include "CpuUsageInfo.h"
#include "Component.h"
#include "Macro.h"
#include "stdint.h"
#include <memory>

namespace Environment {
    class CpuUsageInfo;
}

namespace SystemMonitor {

class ISystemMonitorHandler;

class SystemInfoCollector : public EventHandler::IEvent
{
    uint64_t eventId_;
    std::shared_ptr<ISystemMonitorHandler> monitorHandler_;
public:
    SystemInfoCollector(std::shared_ptr<ISystemMonitorHandler> monitorHandler);
    virtual ~SystemInfoCollector();
protected:
    virtual uint64_t getEventId() const;
    virtual void run(EventHandler::EventFlag flag = EventHandler::EventFlag::Event_NoFlag);
    virtual std::ostream& operator<< (std::ostream& os) const;
private:
    void init();

public:
     GETCLASSNAME(SystemInfoCollector)
};

}
#endif // _SYSTEMMONITOR_SYSTEMINFOCOLLECTOR_H_
