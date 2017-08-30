#ifndef _SSHWRAPPER_ISSHCLIENTSESION_H_
#define _SSHWRAPPER_ISSHCLIENTSESION_H_
#include "SftpDirAttribute.h"
#include <string>
namespace SshWrapper
{
class ISshClientSession
{
public:
        ISshClientSession() {}
	virtual ~ISshClientSession() {}

	virtual bool setup() = 0;
	virtual bool shutdown() = 0;
    virtual bool startShellChannel() = 0;
    virtual bool executeShellCommand(const std::string& cmd, std::string& cmdOutput) = 0;
    virtual bool shutdownShellChannel() = 0;

    virtual bool startFtpSession() = 0;
    virtual bool getFile(const std::string& remoteFile, const std::string& localDir) = 0;
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir) = 0;
	virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes) = 0;
    virtual bool shutdownFtpSessionl() = 0;

};

}
#endif
