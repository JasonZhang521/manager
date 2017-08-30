#include "SshClientSession.h"
#include "SshShellChannel.h"
#include "SshFtpSession.h"
#include "App.h"
#include "Trace.h"

#include <string>
#include <sstream>
#include "libssh/libssh.h"
namespace SshWrapper
{

SshClientSession::SshClientSession(ssh_session session, const SshConfigure& configure)
:session_(session)
,configure_(configure)
,shellChannel_(NULL)
,sftpSession_(NULL)
{
    if (session_ == NULL)
    {
        TRACE_WARNING("Ssh session is NULL");
        App::ExitNormal();
    }
}

SshClientSession::SshClientSession(ssh_session session, ISshShellChannel* channel, const SshConfigure& configure)
:session_(session)
,configure_(configure)
,shellChannel_(channel)
,sftpSession_(NULL)
{
    if (session_ == NULL)
    {
        TRACE_WARNING("Ssh session is NULL");
        App::ExitNormal();
    }

    if (shellChannel_ == NULL)
    {
        TRACE_WARNING("Ssh shell channel is NULL");
        App::ExitNormal();
    }
}

SshClientSession::SshClientSession(ssh_session session, ISshFtpSession* sftpSession, const SshConfigure& configure)
:session_(session)
,configure_(configure)
,shellChannel_(NULL)
,sftpSession_(sftpSession)
{
    if (session_ == NULL)
    {
        TRACE_WARNING("Ssh session is NULL");
        App::ExitNormal();
    }

    if (sftpSession == NULL)
    {
        TRACE_WARNING("Sftp session is NULL");
        App::ExitNormal();
    }
}

SshClientSession::SshClientSession(ssh_session session, ISshShellChannel* channel, ISshFtpSession* sftpSession, const SshConfigure& configure)
:session_(session)
,configure_(configure)
,shellChannel_(channel)
,sftpSession_(sftpSession)
{
    if (session_ == NULL)
    {
        TRACE_WARNING("Ssh session is NULL");
        App::ExitNormal();
    }

    if (shellChannel_ == NULL)
    {
        TRACE_WARNING("Ssh shell channel is NULL");
        App::ExitNormal();
    }

    if (sftpSession == NULL)
    {
        TRACE_WARNING("Sftp session is NULL");
        App::ExitNormal();
    }
}

SshClientSession::~SshClientSession()
{
    if (session_ != NULL)
    {
	ssh_free(session_);
    }
    if (shellChannel_ != NULL)
    {
        delete shellChannel_;
    }
}

void SshClientSession::configure(const SshConfigure& config)
{
	configure_ = config;
}

void SshClientSession::setOptions()
{
    TRACE_NOTICE("Set option for client session!");
    ssh_options_set(session_, SSH_OPTIONS_HOST, configure_.host.c_str());
    ssh_options_set(session_, SSH_OPTIONS_LOG_VERBOSITY, &configure_.verbosity);
    ssh_options_set(session_, SSH_OPTIONS_PORT, &configure_.port);
}

bool SshClientSession::setup()
{
    TRACE_NOTICE("Set up a new ssh session for client session!");
    // Set options.
	setOptions();
	// Connect
	if(!connect())
	{
		return false;
	}

	if (!verifyKnownhost())
	{
		return false;
	}

	if (!verifyUser())
    {
		return false;
	}

   
	return true;
}

bool SshClientSession::shutdown()
{
    TRACE_NOTICE("Shutdown the ssh session for client session!");
	disconnect();
    return true;
}

bool SshClientSession::connect()
{
    TRACE_NOTICE("ssh session is connecting to the server!");
	int rc = ssh_connect(session_);
	if (rc != SSH_OK)
	{
	    TRACE_WARNING("Error connection to" << configure_.host << "! error info: " << ssh_get_error(session_));
		return false;
    }
	return true;
}

bool SshClientSession::startShellChannel()
{
    TRACE_NOTICE("Start Shell Channel for client session!");
	if (shellChannel_ == NULL)
	{
		shellChannel_ = new SshShellChannel(session_);
	}
    return shellChannel_->setup();
}

bool SshClientSession::executeShellCommand(const std::string& cmd, std::string& cmdOutput)
{
    TRACE_NOTICE("execute shell command (" << cmd << ") for client session!");
    if (shellChannel_ == NULL)
    {
        TRACE_WARNING("Ssh shell channel is NULL");
        App::ExitNormal();
    }
    return shellChannel_->executeCommand(cmd, cmdOutput);
}

bool SshClientSession::shutdownShellChannel()
{
    TRACE_NOTICE("Start Shell Channel for client session!");
    bool rc = shellChannel_->shutdown();
	delete shellChannel_;
    shellChannel_ = NULL;
    return rc;
}

bool SshClientSession::startFtpSession()
{
    if (sftpSession_ == NULL)
    {
        sftpSession_ = new SshFtpSession(session_);
    }
    return sftpSession_->setup();
}

bool SshClientSession::getFile(const std::string& remoteFile, const std::string& localDir)
{
    if (sftpSession_ == NULL)
    {
        TRACE_WARNING("Ssh ftp session is NULL");
        App::ExitNormal();
    }
    return sftpSession_->getFile(remoteFile, localDir);
}

bool SshClientSession::putFile(const std::string& localFile, const std::string& remoteDir)
{
    if (sftpSession_ == NULL)
    {
        TRACE_WARNING("Ssh ftp session is NULL");
        App::ExitNormal();
    }
    return sftpSession_->putFile(localFile, remoteDir);
}

bool SshClientSession::listDir(const std::string& dirPath, SftpDirAttributes& dirAttributes)
{
    if (sftpSession_ == NULL)
    {
        TRACE_WARNING("Ssh ftp session is NULL");
        App::ExitNormal();
    }
    return sftpSession_->listDir(dirPath, dirAttributes);
}

bool SshClientSession::shutdownFtpSessionl()
{
    bool rc = sftpSession_->shutdown();
    delete sftpSession_;
    sftpSession_ = NULL;
    return rc;
}

void SshClientSession::disconnect()
{
	ssh_disconnect(session_);
}

bool SshClientSession::verifyKnownhost()
{
	 unsigned char *hash = NULL;
	 int state = ssh_is_server_known(session_);
	 int hlen = ssh_get_pubkey_hash(session_, &hash);
	 if (hlen < 0)
		 return -1;
	 char *hexa = 0;;
	 switch (state)
	 {
		 case SSH_SERVER_KNOWN_OK:
			 break; /* ok */
		 case SSH_SERVER_KNOWN_CHANGED:
			 hexa = ssh_get_hexa(hash, hlen);
			 TRACE_WARNING("Host key for server changed: it is now:\n" << hexa
					 << "\nFor security reasons, connection will be stopped");
			 free(hexa);
			 free(hash);
			 return false;
		 case SSH_SERVER_FOUND_OTHER:
			 TRACE_WARNING("The host key for this server was not found but an other ype of key exists. "
					 << "An attacker might change the default server key to confuse your client into thinking the key does not exist!");
			 free(hash);
			 return false;
		 case SSH_SERVER_FILE_NOT_FOUND:
			 TRACE_WARNING("Could not find known host files."
					 << "If you accept the host key here, the file will be automatically created.");
			 /* fallback to SSH_SERVER_NOT_KNOWN behavior */
		 case SSH_SERVER_NOT_KNOWN:
			 hexa = ssh_get_hexa(hash, hlen);
			 TRACE_WARNING("The server is unknown. Do you trust the host key?"
					 << (configure_.unknownHostContinue ? "Yes" : "No"));
             TRACE_WARNING("Public key hash:" << hexa);
			 free(hexa);
			 if (configure_.unknownHostContinue)
			 {
				 if (ssh_write_knownhost(session_) < 0)
				 {
					 TRACE_WARNING("Error write host, error info:" << ssh_get_error(session_));
					 free(hash);
					 return false;
				 }
			 }
			 else
			 {
				 return false;
			 }
			 break;
		 case SSH_SERVER_ERROR:
			 TRACE_WARNING("Error:" << ssh_get_error(session_));
			 free(hash);
			 return false;
	 }
	 free(hash);
	 return true;
}

bool SshClientSession::verifyUser()
{
	 // Authenticate ourselves
	 // char* password = getpass("Password: ");
	 // std::cout << password << std::endl;
	 int rc = ssh_userauth_password(session_, configure_.user.c_str(), configure_.password.c_str());
	 if (rc != SSH_AUTH_SUCCESS)
	 {
	     TRACE_WARNING("Error authenticating with password: " << ssh_get_error(session_));

		 return false; 
     }
	 return true;
}



}
