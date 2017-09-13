#ifndef FILEPATHHANDLER_H
#define FILEPATHHANDLER_H
#include <string>

class FilePathHandler
{
public:
    FilePathHandler();
    static std::string getFileName(const std::string& fullPath);
    static std::string getFileDir(const std::string& fullPath);
    static bool isFileExist(const std::string& fullPath);
    static std::string generateUniqueFileName(const std::string& fullPath);
    static std::string getIndexFileName(const std::string& fullPath, size_t index);
};

#endif // FILEPATHHANDLER_H
