#ifndef SYSTEMERRORINFO_H
#define SYSTEMERRORINFO_H
#include <string>
#include <string.h>
#ifdef WIN32
#include <winsock2.h>
#endif
namespace PlatformWrapper {

#ifdef WIN32
inline int GetLastErrorNo()
{
    return ::WSAGetLastError();
}
std::string GetErrorMessageFromErrorCode(int errorCode);
std::string GetLastErrorMessage();
#else
inline int GetLastErrorNo()
{
    return errno;
}

inline std::string GetErrorMessageFromErrorCode(int errorCode)
{
    return ::strerror(errno);
}

inline std::string GetLastErrorMessage()
{
    return GetErrorMessageFromErrorCode(GetLastErrorNo());
}
#endif


}
#endif // SYSTEMERRORINFO_H
