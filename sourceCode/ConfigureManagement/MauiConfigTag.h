#ifndef _CONFIGUREMANAGEMENT_MAUICONFIGTAG_H_
#define _CONFIGUREMANAGEMENT_MAUICONFIGTAG_H_
#include <set>
#include <map>

namespace ConfigureManagement {

class MauiConfigTag
{
    static const std::set<std::string> SingleTags;
    static const std::set<std::string> MultiTags;
    static const std::map<std::string, std::set<std::string> > SubTags;
public:
    MauiConfigTag();
    static bool IsSingeTag(const std::string& tag);
    static bool IsMultiTag(const std::string& tag);
    static bool IsSubTag(const std::string& keyTag, const std::string& tag);
};

}

#endif // _CONFIGUREMANAGEMENT_MAUICONFIGTAG_H_
