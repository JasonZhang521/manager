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
    virtual bool getFileFromLastPos(const std::string& remoteFile, const std::string& localFile) = 0;
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir) = 0;
	virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes) = 0;
    virtual void stopGetFile() = 0;
    virtual void stopPutFile() = 0;
    virtual bool listRemoteFileAttribute(const std::string& filePath, SftpFileAttribute& fileAttributes) = 0;
    virtual bool isRemoteFileExist(const std::string& remoteFile) = 0;
    virtual bool renameRemoteFile(const std::string& srcFile, const std::string& dstFile) = 0;
    virtual bool shutdownFtpSessionl() = 0;

};

}
#endif
