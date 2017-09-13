#include "SystemErrorInfo.h"

namespace PlatformWrapper {
#ifdef WIN32
std::string GetLastErrorMessage()
{
    int nErrno = WSAGetLastError();
    return GetErrorMessageFromErrorCode(nErrno);
}

std::string GetErrorMessageFromErrorCode(int errorCode)
{
    LPTSTR lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
        );
    std::string errorMsg = std::string(reinterpret_cast<char*>(lpMsgBuf));
    LocalFree(lpMsgBuf);
    return errorMsg;
}
#endif

}
