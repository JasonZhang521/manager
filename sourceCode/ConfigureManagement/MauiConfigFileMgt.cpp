#include "MauiConfigFileMgt.h"
#include "RemoveCharacter.h"
#include "FilePathHandler.h"
#include "Trace.h"
#include <fstream>
#include <sstream>

namespace ConfigureManagement {

MauiConfigFileMgt::MauiConfigFileMgt(const std::string& filePath)
    :filePath_(filePath)
{
}

void MauiConfigFileMgt::openFileAndParse()
{
    std::ifstream ifs(filePath_.c_str());
    if (!ifs.good())
    {
        TRACE_NOTICE("Failed to open file: " << filePath_ << ", stop reading, try next time." << std::endl);
        return;
    }

    std::vector<MauiConfigRecord> configRecords;
    char buffer[512];
    while(ifs.good())
    {
        std::fill(buffer, buffer + 512, 0);
        ifs.getline(buffer, 512);
        std::string line(buffer);
        parsesRecord(configRecords, line);
    }

    config_ = configRecords;
}

void MauiConfigFileMgt::updateConfigure(const MauiConfig& newConfig)
{
    const std::vector<MauiConfigRecord>& newRecords = newConfig.getRecords();

    for (auto record : newRecords)
    {
        config_.updateRecord(record);
    }
}

void MauiConfigFileMgt::replaceConfigure(const MauiConfig& newConfig)
{
    config_ = newConfig;
}

void MauiConfigFileMgt::parsesRecord(std::vector<MauiConfigRecord>& records, const std::string& line)
{
    RemoveCharacter remover;
    std::string str = remover(line);
    remover.setCharacter('\t');
    str = remover(str);

    size_t posFirstSpace = line.find(' ');
    size_t posFirstSqure = line.find('[');
    if (posFirstSpace < posFirstSqure)
    {
        const std::string titleTag = str.substr(0, posFirstSpace);
        str = str.substr(posFirstSpace + 1, str.size() - posFirstSpace - 1);
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        const std::string titleValue = remover(str);
        MauiTagValue title(titleTag, titleValue);
        MauiConfigRecord record(title);
        records.push_back(record);
    }
    else
    {
        const std::string titleTag = str.substr(0, posFirstSqure);
        str = str.substr(posFirstSpace + 1, str.size() - posFirstSpace - 1);
        size_t posSecondSqure = str.find(']');
        const std::string titleValue = str.substr(posSecondSqure);
        MauiTagValue title(titleTag, titleValue);
        MauiConfigRecord record(title, true);
        str = str.substr(posSecondSqure + 1, str.size() - posSecondSqure - 1);
        remover.setCharacter(' ');
        str = remover(str);
        remover.setCharacter('\t');
        str = remover(str);
        parsesSubRecord(record, str);
    }
}

void MauiConfigFileMgt::parsesSubRecord(MauiConfigRecord& record, const std::string& subLine)
{
    std::vector<MauiTagValue> tagValues;
    RemoveCharacter remover;
    size_t posEqual = subLine.find('=');
    std::string str = subLine;
    while (posEqual != std::string::npos)
    {
        std::string tag = str.substr(0, posEqual);
        str = str.substr(posEqual + 1, str.size() - posEqual - 1);

        remover.setCharacter(' ');
        tag = remover(tag);
        str = remover(str);
        remover.setCharacter('\t');
        tag = remover(tag);
        str = remover(str);

        size_t posSpace = str.find(' ');
        std::string value = str.substr(0, posSpace);
        str = str.substr(posSpace + 1, str.size() - posSpace - 1);

        remover.setCharacter(' ');
        value = remover(value);
        str = remover(str);
        remover.setCharacter('\t');
        value = remover(value);
        str = remover(str);

        MauiTagValue tagValue(tag, value, true);
        tagValues.push_back(tagValue);

        posEqual = str.find('=');
    }
    record.setSubItems(tagValues);
}

void MauiConfigFileMgt::backup() const
{
    const std::string fileDir = FilePathHandler::getFileDir(filePath_);
    const std::string fileName = FilePathHandler::getFileName(filePath_);

    // delete the ".config.10" file
    {
        std::stringstream ss;
        ss << 10;
        const std::string tempFileName = "." + fileName + "." + ss.str();
        const std::string tempFilePath = fileDir + "/" + tempFileName;
        if (FilePathHandler::isFileExist(tempFilePath))
        {
            std::string shellCmd = "rm " + tempFilePath;
            system(shellCmd.c_str());
        }
    }

    // mv the ".config.x" to ".config.x+1"
    for (int i = 9; i >= 0; --i)
    {
        std::stringstream ss;
        ss << i;
        const std::string oldTempFileName = "." + fileName + "." + ss.str();
        const std::string oldTempFilePath = fileDir + "/" + oldTempFileName;
        if (FilePathHandler::isFileExist(oldTempFilePath))
        {
            std::stringstream ss1;
            ss1 << i + 1;
            const std::string newTempFileName = "." + fileName + "." + ss1.str();
            const std::string newTempFilePath = fileDir + "/" + newTempFileName;
            std::string shellCmd = "mv " + oldTempFileName + " " + newTempFilePath;
            system(shellCmd.c_str());
        }
    }

    // mv the "config" to ".config.0"
    {
        std::stringstream ss;
        ss << 0;
        const std::string tempFileName = "." + fileName + "." + ss.str();
        const std::string tempFilePath = fileDir + "/" + tempFileName;
        if (FilePathHandler::isFileExist(tempFilePath))
        {
            std::string shellCmd = "mv " + filePath_ + " " + tempFilePath;
            system(shellCmd.c_str());
        }
    }
}

}
