#include "SshClient.h"
#include "SshClientSession.h"
#include "App.h"
#include "Trace.h"

namespace SshWrapper
{

SshClient::SshClient(ISshClientSession* session)
: session_(session)
{
	if (session_ == NULL)
	{
	    TRACE_WARNING("Session is NULL when initial shell channel!");
		App::ExitNormal();
	}
}

SshClient::~SshClient()
{
	if (session_ != NULL)
	{
		delete session_;
	}
}

bool SshClient::setup()
{
	return session_->setup();
}
bool SshClient::shutdown()
{
	return session_->shutdown();
}
bool SshClient::startShell()
{
	return session_->startShellChannel();
}
bool SshClient::shutdownShell()
{
	return session_->shutdownShellChannel();
}
bool SshClient::executeShellCommand(const std::string& cmd, std::string& cmdOutput)
{
	return session_->executeShellCommand(cmd, cmdOutput);
}

bool SshClient::startSftp()
{
    return session_->startFtpSession();
}

bool SshClient::shutdownSftp()
{
    return session_->shutdownFtpSessionl();
}

bool SshClient::getFile(const std::string& remoteFile, const std::string& localDir)
{
    return session_->getFile(remoteFile, localDir);
}

bool SshClient::putFile(const std::string& localFile, const std::string& remoteDir)
{
    return session_->putFile(localFile, remoteDir);
}

bool SshClient::listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes)
{
	return session_->listDir(dirPath, dirAttributes);
}

}
