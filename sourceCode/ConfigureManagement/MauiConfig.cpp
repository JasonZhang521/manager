#include "MauiConfig.h"
#include "WriteBuffer.h"
#include "ReadBuffer.h"
#include <algorithm>
#include <ostream>

namespace ConfigureManagement {

// ManuiTagValue

MauiTagValue::MauiTagValue()
    : isSubTag_(false)
{

}

MauiTagValue::MauiTagValue(const MauiTagValue& tagValue)
    : tag_(tagValue.tag_)
    , value_(tagValue.value_)
    , isSubTag_(tagValue.isSubTag_)
{
}

MauiTagValue::MauiTagValue(const std::string& tag, const std::string& value, bool isSubTag)
    : tag_(tag)
    , value_(value)
    , isSubTag_(isSubTag)
{

}

MauiTagValue& MauiTagValue::operator = (const MauiTagValue& tagValue)
{
    tag_ = tagValue.tag_;
    value_ = tagValue.value_;
    isSubTag_ = tagValue.isSubTag_;
    return *this;
}

bool MauiTagValue::operator == (const MauiTagValue& tagValue) const
{
    return (tag_ == tagValue.tag_ &&
            value_ == tagValue.value_ &&
            isSubTag_ == tagValue.isSubTag_);
}

bool MauiTagValue::operator != (const MauiTagValue& tagValue) const
{
    return !operator ==(tagValue);
}

std::ostream& MauiTagValue::operator << (std::ostream& os) const
{
    if (isSubTag_)
    {
        os << tag_ << "=" << value_;
    }
    else
    {
        os << tag_ << " " << value_;
    }
    return os;
}

const std::string& MauiTagValue::getTag() const
{
    return tag_;
}

const std::string& MauiTagValue::getValue() const
{
    return value_;
}

void MauiTagValue::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(isSubTag_);
    writeBuffer.write(static_cast<uint8_t>(tag_.size()));
    writeBuffer.write(tag_.c_str(), tag_.size());
    writeBuffer.write(static_cast<uint8_t>(value_.size()));
    writeBuffer.write(value_.c_str(), tag_.size());
}

void MauiTagValue::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read(isSubTag_);

    char buffer[256];
    std::fill(buffer, buffer + 256, 0);
    uint8_t size = 0;

    readBuffer.read(size);
    readBuffer.read(buffer, size);
    tag_ = std::string(buffer, size);

    readBuffer.read(size);
    readBuffer.read(buffer, size);
    value_ = std::string(buffer, size);
}

// ManuiConfigRecord

MauiConfigRecord::MauiConfigRecord()
    : isMultiTag_(false)
{

}

MauiConfigRecord::MauiConfigRecord(MauiTagValue title, bool isMultiTag)
    : title_(title)
    , isMultiTag_(isMultiTag)
{

}

MauiConfigRecord::MauiConfigRecord(const MauiConfigRecord& configureRecord)
    : title_(configureRecord.title_)
    , isMultiTag_(configureRecord.isMultiTag_)
    , subItems_(configureRecord.subItems_)
{

}

MauiConfigRecord& MauiConfigRecord::operator = (const MauiConfigRecord& configureRecord)
{
    title_ = configureRecord.title_;
    isMultiTag_ = configureRecord.isMultiTag_;
    subItems_ = configureRecord.subItems_;
    return *this;
}

bool MauiConfigRecord::operator == (const MauiConfigRecord& configureRecord) const
{
    if (title_ != configureRecord.title_ ||
        isMultiTag_ != configureRecord.isMultiTag_ ||
        subItems_.size() != configureRecord.subItems_.size())
    {
        return false;
    }

    for (size_t i = 0; i < subItems_.size(); ++i)
    {
        if (std::find(subItems_.begin(), subItems_.end(), configureRecord.subItems_[i]) == subItems_.end())
        {
            return false;
        }
    }

    return true;
}

bool MauiConfigRecord::operator != (const MauiConfigRecord& configureRecord) const
{
    return !operator ==(configureRecord);
}

std::ostream& MauiConfigRecord::operator << (std::ostream& os) const
{
    if (isMultiTag_)
    {
        os << title_.getTag() << "[" << title_.getValue() << "]";
        for (auto tagValue : subItems_)
        {
            os << " ";
            os << tagValue;
        }
    }
    else
    {
        os << title_;
    }

    return os;
}

void MauiConfigRecord::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(isMultiTag_);
    title_.serialize(writeBuffer);
    writeBuffer.write(static_cast<uint16_t>(subItems_.size()));
    for (auto it : subItems_)
    {
        it.serialize(writeBuffer);
    }
}

void MauiConfigRecord::unserialize(Serialize::ReadBuffer& readBuffer)
{
    readBuffer.read(isMultiTag_);
    title_.unserialize(readBuffer);

    std::vector<MauiTagValue> subItems;
    uint16_t size = 0;
    readBuffer.read(size);
    for (uint16_t i = 0; i < size; ++i)
    {
        MauiTagValue tagValue;
        tagValue.unserialize(readBuffer);
        subItems.push_back(tagValue);
    }
    subItems_.swap(subItems);
}


MauiConfig::MauiConfig()
{
}

MauiConfig::MauiConfig(const MauiConfig& config)
    : records_(config.records_)
{

}

MauiConfig::MauiConfig(const std::vector<MauiConfigRecord>& records)
    :records_(records)
{

}

bool MauiConfig::operator == (const MauiConfig& configure) const
{
    if (records_.size() != configure.records_.size())
    {
        return false;
    }

    for (auto record : configure.records_)
    {
        if (std::find(records_.begin(), records_.end(), record) == records_.end())
        {
            return false;
        }
    }

    return true;
}

bool MauiConfig::operator != (const MauiConfig& configure) const
{
    return !operator ==(configure);
}

std::ostream& MauiConfig::operator << (std::ostream& os) const
{
    for (auto record : records_)
    {
        os << record << std::endl;
    }
    return os;
}

const std::vector<MauiConfigRecord>& MauiConfig::getRecords() const
{
    return records_;
}

void MauiConfig::setRecords(const std::vector<MauiConfigRecord>& records)
{
    records_ = records;
}

void MauiConfig::updateRecord(const MauiConfigRecord& newRecord)
{
    std::vector<MauiConfigRecord>::iterator insertPos = records_.end();
    bool updated = false;
    for (std::vector<MauiConfigRecord>::iterator it = records_.begin(); it != records_.end(); ++it)
    {
        MauiConfigRecord& oldRecord = *it;
        if (oldRecord.getTitle() == newRecord.getTitle())
        {
            oldRecord = newRecord;
            updated = true;
            break;
        }
        else
        {
            if (insertPos == records_.end() && oldRecord.getTitle().getTag() == newRecord.getTitle().getTag())
            {
                insertPos = it;
            }
        }
    }

    if (!updated)
    {
        records_.insert(insertPos, newRecord);
    }
}

void MauiConfig::serialize(Serialize::WriteBuffer& writeBuffer) const
{
    writeBuffer.write(static_cast<uint16_t>(records_.size()));
    for (auto record : records_)
    {
        record.serialize(writeBuffer);
    }
}

void MauiConfig::unserialize(Serialize::ReadBuffer& readBuffer)
{
    std::vector<MauiConfigRecord> records;
    uint16_t size = 0;
    readBuffer.read(size);
    for (uint16_t i = 0; i < size; ++i)
    {
        MauiConfigRecord record;
        record.unserialize(readBuffer);
        records.push_back(record);
    }

    records_.swap(records);
}

}
