#ifndef _SSHWRAPPER_SSHCLIENTSESSION_H_
#define _SSHWRAPPER_SSHCLIENTSESSION_H_
#include "ISshClientSession.h"
#include "SshConfigure.h"
#include "Component.h"
#include "Macro.h"
#include <map>
#include <string>

struct ssh_session_struct;
typedef struct ssh_session_struct* ssh_session;

namespace SshWrapper
{
class ISshShellChannel;
class ISshFtpSession;

class SshClientSession : public ISshClientSession
{
    ssh_session session_;
    SshConfigure configure_;
    ISshShellChannel* shellChannel_;
    ISshFtpSession* sftpSession_;
public:
    SshClientSession(ssh_session session, const SshConfigure& configure);
    SshClientSession(ssh_session session, ISshShellChannel* channel, const SshConfigure& configure);
    SshClientSession(ssh_session session, ISshFtpSession* sftpSession, const SshConfigure& configure);
    SshClientSession(ssh_session session, ISshShellChannel* channel, ISshFtpSession* sftpSession, const SshConfigure& configure);
    virtual ~SshClientSession();

    void configure(const SshConfigure& config);

protected:
    virtual bool setup();
    virtual bool shutdown();
    virtual bool startShellChannel();
    virtual bool executeShellCommand(const std::string& cmd, std::string& cmdOutput);
    virtual bool shutdownShellChannel();

    virtual bool startFtpSession();
    virtual bool getFile(const std::string& remoteFile, const std::string& localDir);
    virtual bool putFile(const std::string& localFile, const std::string& remoteDir);
    virtual bool listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes);
    virtual bool shutdownFtpSessionl();
private:
    void setOptions();
    bool connect();
    void disconnect();
    bool verifyKnownhost();
    bool verifyUser();

public:
    GETCLASSNAME(SshClientSession)
};

}
#endif
