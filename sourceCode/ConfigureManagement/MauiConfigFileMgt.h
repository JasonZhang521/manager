#ifndef _CONFIGUREMANAGEMENT_MAUICONFIGFILEMGT_H_
#define _CONFIGUREMANAGEMENT_MAUICONFIGFILEMGT_H_
#include "MauiConfig.h"
#include "Component.h"
#include "Macro.h"
#include <string>

namespace ConfigureManagement {

class MauiConfigFileMgt
{
    std::string filePath_;
    MauiConfig config_;
public:
    MauiConfigFileMgt(const std::string& filePath);
    void openFileAndParse();
    void updateConfigure(const MauiConfig& newConfig);
    void replaceConfigure(const MauiConfig& newConfig);
private:
    void parsesRecord(std::vector<MauiConfigRecord>& records, const std::string& line);
    void parsesSubRecord(MauiConfigRecord& record, const std::string& subLine);
    void backup() const;
public:
     GETCLASSNAME(CpuInfoBriefly)
};

}
#endif // _CONFIGUREMANAGEMENT_MAUICONFIGFILEMGT_H_
