#include "FilePathHandler.h"

#include <fstream>
#include <sstream>

FilePathHandler::FilePathHandler()
{

}

std::string FilePathHandler::getFileName(const std::string& fullPath)
{
    size_t pos = fullPath.rfind('/');
    if (pos == std::string::npos)
    {
        pos = fullPath.rfind('\\');
    }

    if (pos == std::string::npos)
    {
        return fullPath;
    }
    else
    {
		if (pos == fullPath.size())
		{
			return "";
		}
        return fullPath.substr(pos + 1);
    }
}

std::string FilePathHandler::getFileDir(const std::string& fullPath)
{
    size_t pos = fullPath.rfind('/');
    if (pos == std::string::npos)
    {
        pos = fullPath.rfind('\\');
    }

    if (pos == std::string::npos)
    {
        return fullPath;
    }
    else
    {
        return fullPath.substr(0, pos);
    }
}

 bool FilePathHandler::isFileExist(const std::string& fullPath)
 {
    std::fstream file;
    file.open(fullPath.c_str(), std::ios_base::in);
    if (!file)
    {
        return false;
    }
    else
    {
        return true;
    }
 }

std::string FilePathHandler::generateUniqueFileName(const std::string& fullPath)
{
    std::string tempFileName = fullPath;
    unsigned int index = 1;
    while (isFileExist(tempFileName))
    {
       tempFileName = getIndexFileName(fullPath, index);
       ++index;
    }
    return tempFileName;
}

std::string FilePathHandler::getIndexFileName(const std::string& fullPath, size_t index)
{
    std::string tempFileName = fullPath;
    std::stringstream sstr;
    sstr << index;
    tempFileName = fullPath + "_" + sstr.str();
    return tempFileName;
}
