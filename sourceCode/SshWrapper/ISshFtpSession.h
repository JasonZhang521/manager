#ifndef _WRAPPER_ISSHFTPSESSION_H_
#define _WRAPPER_ISSHFTPSESSION_H_
#include "SftpDirAttribute.h"
#include <string>

namespace SshWrapper
{

class ISshFtpSession
{
public:
    ISshFtpSession() {}
    virtual ~ISshFtpSession() {}
    virtual bool setup() = 0;
    virtual bool shutdown() = 0;
    virtual bool getFile(const std::string& remoteFile, const std::string& localDir) = 0;
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir) = 0;
	virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes) = 0;
};

}
#endif // ISSHFTPSESSION_H
