#include <string>
#include <map>
#include <sstream>
#include <libssh/libssh.h>
#include "App.h"
#include "Trace.h"
#include "SshClient.h"
SshClient::SshClient(bool unknownHostContinue, const std::string& user,
		const std::string& password, const std::string& host, int verbosity, int port)
:session_(ssh_new())
,unknownHostContinue_(unknownHostContinue)
,user_(user)
,password_(password)	
,host_(host)
,verbosity_(verbosity)
,port_(port)
,cliChannel_(0)
{
    if (session_ == NULL)
	{
	    TRACE_WARNING("Set up a new ssh session_ for client failed!");
		App::ExitNormal();
	}
}

SshClient::~SshClient()
{
	ssh_free(session_);
}

bool SshClient::setup()
{
	TRACE_NOTICE("Set up a new ssh session_ for client!");
    // Set options.
	setDefaultOptions();
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

void SshClient::shutdown()
{
	TRACE_NOTICE("Shutdow the ssh session_ for client!");
	disconnect();
}

void SshClient::setDefaultOptions()
{
    ssh_options_set(session_, SSH_OPTIONS_HOST, host_.c_str());
    ssh_options_set(session_, SSH_OPTIONS_LOG_VERBOSITY, &verbosity_);
    ssh_options_set(session_, SSH_OPTIONS_PORT, &port_);
}

void SshClient::setOptions(const OptionsMap& options)
{
	for (OptionsMap::const_iterator it = options.begin(); it != options.end(); ++it)
	{
       int res = ssh_options_set(session_, static_cast<ssh_options_e>(it->first), it->second);
	   if (res < 0)
	   {
	       TRACE_ERROR("Set options for ssh session error: option = " << it->first << ", value = " << it->second);
		   App::ExitWithCoredump();
	   }
	}
}

bool SshClient::executeCliCommand(const std::string& cli, std::string& cliResult)
{
	if (!openCliChannel())
	{
		return false;
	}
	
    int rc = ssh_channel_request_exec(cliChannel_, cli.c_str());
    if (rc != SSH_OK)
	{
        closeCliChannel();
	    return false;
	}

	std::stringstream sstr;
	char buffer[256];
	int nbytes = ssh_channel_read(cliChannel_, buffer, sizeof(buffer), 0);
	while (nbytes > 0)
	{
		buffer[nbytes] = 0;
		sstr << buffer;
		nbytes = ssh_channel_read(cliChannel_, buffer, sizeof(buffer), 0);
	}
    cliResult = sstr.str();
	if (nbytes < 0)
	{
        closeCliChannel();
	    return false;
	}
	ssh_channel_send_eof(cliChannel_);
    closeCliChannel();
	return true;
}

bool SshClient::connect()
{
	int rc = ssh_connect(session_);
	if (rc != SSH_OK)
	{
	    TRACE_WARNING("Error connection to" << host_ << "! error info: " << ssh_get_error(session_));
		return false;
    }
	return true;
}

void SshClient::disconnect()
{
	ssh_disconnect(session_);
}

bool SshClient::verifyKnownhost()
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
					 << (unknownHostContinue_ ? "Yes" : "No"));
             TRACE_WARNING("Public key hash:" << hexa);
			 free(hexa);
			 if (unknownHostContinue_)
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

bool SshClient::verifyUser()
{
	 // Authenticate ourselves
	 // char* password = getpass("Password: ");
	 // std::cout << password << std::endl;
	 int rc = ssh_userauth_password(session_, user_.c_str(), password_.c_str());
	 if (rc != SSH_AUTH_SUCCESS)
	 {
	     TRACE_WARNING("Error authenticating with password: " << ssh_get_error(session_));
		 return false; 
	 }
	 return true;
}

bool SshClient::openCliChannel()
{
	TRACE_NOTICE("Open Cli Channel!");
	if (NULL == cliChannel_)
	{
        cliChannel_ = ssh_channel_new(session_);
	}
    if (cliChannel_ == NULL)
	{
		TRACE_WARNING("Error create new Channel:" << ssh_get_error(session_));
	    return false;
	}
    int rc = ssh_channel_open_session(cliChannel_);
    if (rc != SSH_OK)
    {
		TRACE_WARNING("Error open new Channel:" << ssh_get_error(session_));
	    ssh_channel_free(cliChannel_);
		cliChannel_ = NULL;
	    return false;
    }
	return true;
}

void SshClient::closeCliChannel()
{
	TRACE_NOTICE("Close Cli Channel!");
    ssh_channel_close(cliChannel_);
    ssh_channel_free(cliChannel_);
	cliChannel_ = NULL;
}
