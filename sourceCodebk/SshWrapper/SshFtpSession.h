#ifndef _WRAPPER_SSHFTPSESSION_H_
#define _WRAPPER_SSHFTPSESSION_H_
#include "ISshFtpSession.h"
#include "Component.h"
#include "Macro.h"

struct ssh_session_struct;
typedef struct ssh_session_struct* ssh_session;
struct sftp_session_struct;
typedef struct sftp_session_struct* sftp_session;

namespace SshWrapper
{

#define MAX_XFER_BUF_SIZE 16384

class SshFtpSession : public ISshFtpSession
{
    ssh_session session_;
    sftp_session sftpSession_;
public:
    SshFtpSession(ssh_session session);
    ~SshFtpSession();

protected:
    virtual bool setup();
    virtual bool shutdown();
    virtual bool getFile(const std::string& remoteFile, const std::string& localDir);
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir);
    virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes);

private:
    bool isRemoteFileExit(const std::string& remoteDir, const std::string& fileName);

public:
     GETCLASSNAME(SshFtpSession)
};

}
#endif // SSHFTPSESSION_H
