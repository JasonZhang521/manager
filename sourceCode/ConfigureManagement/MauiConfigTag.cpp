#include "MauiConfigTag.h"
namespace ConfigureManagement {

const std::set<std::string> MauiConfigTag::SingleTags =
{
    "SERVERPORT"
    "JOBNODEMATCHPOLICY"
    "FSINTERVAL"
    "RMPOLLINTERVAL"
    "NODEACCESSPOLICY"
    "FSQOSWEIGHT"
    "LOGFILE"
    "SRCFGWEIGHT"
    "QUEUETIMEWEIGHT"
    "ENABLEMUITINODEJOBS"
    "ENABLEMULTIREQJOBS"
    "PREEMPTPOLICY"
    "GROUPWEIGHT"
    "LOGFILEMAXSIZE"
    "USERWEIGHT"
    "FSPOLICY"
    "SERVERMODE"
    "QOSWEIGHT"
    "BACKFILLPOLICY"
    "RESERVATIONPOLICY"
    "LOGLEVEL"
    "CLASSWEIGHT"
    "NODEALLOCATIONPOLICY"
    "CREDWEIGHT"
    "CONSUMEDWEIGHT"
    "LOGFILEROLLDEPTH"
    "DEFERTIME"
    "ADMIN1"
    "NODEAVAILABILITYPOLICY"
};

const std::set<std::string> MauiConfigTag::MultiTags =
{
    "RMCFG",
    "USERCFG",
    "QOSCFG",
    "CLASSCFG",
    "NODECFG",
    "SCHEDCFG"
};

const std::map<std::string, std::set<std::string> > MauiConfigTag::SubTags =
{
    {"RMCFG", {"RESOURCETYPE", "CLUSTERQUERYURL", "HOST", "TYPE"}},
    {"USERCFG", {"MAXPROC", "MAXNODE", "MAXJOB"}},
    {"QOSCFG", {"QFLAGS"}},
    {"CLASSCFG", {"PRIORITY"}},
    {"NODECFG", {"INFINITEPRIO", "PRIORITYF", "RESCPUPGPU"}},
    {"SCHEDCFG", {"MODE", "SERVER"}}
};


MauiConfigTag::MauiConfigTag()
{

}

bool MauiConfigTag::IsSingeTag(const std::string& tag)
{
    return (SingleTags.find(tag) != SingleTags.end());
}

bool MauiConfigTag::IsMultiTag(const std::string& tag)
{
    return (MultiTags.find(tag) != MultiTags.end());
}

bool MauiConfigTag::IsSubTag(const std::string& keyTag, const std::string& tag)
{
    std::map<std::string, std::set<std::string> >::const_iterator it = SubTags.find(keyTag);
    return (it != SubTags.cend() && it->second.find(tag) != it->second.cend());
}

}
