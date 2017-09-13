#ifndef _CONFIGUREMANAGEMENT_MANUICONFIG_H_
#define _CONFIGUREMANAGEMENT_MANUICONFIG_H_
#include <string>
#include <vector>

namespace Serialize {
    class WriteBuffer;
    class ReadBuffer;
}

namespace ConfigureManagement {

class MauiTagValue
{
    std::string tag_;
    std::string value_;
    bool isSubTag_;
public:
    MauiTagValue();
    MauiTagValue(const MauiTagValue& tagValue);
    MauiTagValue(const std::string& tag, const std::string& value, bool isSubTag = false);

    MauiTagValue& operator = (const MauiTagValue& tagValue);
    bool operator == (const MauiTagValue& tagValue) const;
    bool operator != (const MauiTagValue& tagValue) const;
    std::ostream& operator << (std::ostream& os) const;

    const std::string& getTag() const;
    const std::string& getValue() const;

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
};

inline std::ostream& operator << (std::ostream& os, const MauiTagValue& tagValue)
{
    return tagValue.operator <<(os);
}

class MauiConfigRecord
{
    MauiTagValue title_;
    bool isMultiTag_;
    std::vector<MauiTagValue> subItems_;
public:
    MauiConfigRecord();
    MauiConfigRecord(MauiTagValue title, bool isMultiTag = false);
    MauiConfigRecord(const MauiConfigRecord& configureRecord);
    MauiConfigRecord& operator = (const MauiConfigRecord& configureRecord);
    bool operator == (const MauiConfigRecord& configureRecord) const;
    bool operator != (const MauiConfigRecord& configureRecord) const;
    std::ostream& operator << (std::ostream& os) const;

    const MauiTagValue& getTitle() const {return title_;}
    void setTitle(const MauiTagValue& title) {title_ = title;}
    const std::vector<MauiTagValue>& getSubItems() const {return subItems_;}
    void setSubItems(const std::vector<MauiTagValue>& subItems)
    {
        subItems_ = subItems;
    }

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
};

inline std::ostream& operator << (std::ostream& os, const MauiConfigRecord& record)
{
    return record.operator <<(os);
}

class MauiConfig
{
    std::vector<MauiConfigRecord> records_;
public:
    MauiConfig();
    MauiConfig(const MauiConfig& config);
    MauiConfig(const std::vector<MauiConfigRecord>& records);

    bool operator == (const MauiConfig& configure) const;
    bool operator != (const MauiConfig& configure) const;
    std::ostream& operator << (std::ostream& os) const;

    const std::vector<MauiConfigRecord>& getRecords() const;
    void setRecords(const std::vector<MauiConfigRecord>& records);
    void updateRecord(const MauiConfigRecord& newRecord);

    void serialize(Serialize::WriteBuffer& writeBuffer) const;
    void unserialize(Serialize::ReadBuffer& readBuffer);
};

inline std::ostream& operator << (std::ostream& os, const MauiConfig& config)
{
    return config.operator <<(os);
}

}

#endif // _CONFIGUREMANAGEMENT_MANUICONFIG_H_
