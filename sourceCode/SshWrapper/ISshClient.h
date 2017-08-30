#ifndef _SSHWRAPPER_ISSHCLIENT_H_
#define _SSHWRAPPER_ISSHCLIENT_H_
#include "SftpDirAttribute.h"
#include <string>

namespace SshWrapper
{

class ISshClient
{
public:
	ISshClient() {}
	virtual ~ISshClient() {}
	virtual bool setup() = 0;
	virtual bool shutdown() = 0;
	virtual bool startShell() = 0;
	virtual bool shutdownShell() = 0;
	virtual bool executeShellCommand(const std::string& cmd, std::string& cmdOutput) = 0;

    virtual bool startSftp() = 0;
    virtual bool shutdownSftp() = 0;
    virtual bool getFile(const std::string& remoteFile, const std::string& localDir) = 0;
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir) = 0;
	virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes) = 0;
};

}
#endif
