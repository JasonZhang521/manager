#include "SshInteractiveShellChannel.h"
#include <string>
#include <map>
#include <sstream>
#include <libssh/libssh.h>
#include "App.h"
#include "Trace.h"

namespace SshWrapper
{

SshInteractiveShellChannel::SshInteractiveShellChannel(ssh_session session, int cols, int rows)
: session_(session)
, channel_(NULL)
, cols_(cols)
, rows_(rows)
{
	if (session == NULL)
	{
		TRACE_WARNING("Session is NULL when initial shell channel!");
		App::ExitNormal();
	}
}

SshInteractiveShellChannel::~SshInteractiveShellChannel()
{
	if (channel_ != NULL)
	{
		ssh_channel_free(channel_);
	}
}

bool SshInteractiveShellChannel::setup()
{
	channel_ = ssh_channel_new(session_);
	if (channel_ == NULL)
	{
		return false;
	}
	int rc = ssh_channel_open_session(channel_);
	if (rc != SSH_OK)
	{
		TRACE_WARNING("Error open new Channel: rc = " << rc << ", error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
		ssh_channel_free(channel_);
		channel_ = NULL;
		return false;
	}
	return true;
}

bool SshInteractiveShellChannel::shutdown()
{
	 ssh_channel_close(channel_);
	 ssh_channel_send_eof(channel_);
	 ssh_channel_free(channel_);
	 channel_ = NULL;
     return false;
}


bool SshInteractiveShellChannel::sessionAndTerminalInit()
{
	 int rc = ssh_channel_request_pty(channel_);
	 if (rc != SSH_OK)
	 {
		TRACE_WARNING("Error request pty: rc = " << rc << ", error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
		 return false;
	 }
	 rc = ssh_channel_change_pty_size(channel_, cols_, rows_);
	 if (rc != SSH_OK)
	 {
		TRACE_WARNING("Error change pty size: rc = " << rc << ", error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
		 return rc;
	 }
	 rc = ssh_channel_request_shell(channel_);
	 if (rc != SSH_OK)
	 {
		TRACE_WARNING("Error request shell: rc = " << rc << ", error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
		 return rc;
	 }

     return true;
}

bool SshInteractiveShellChannel::executeCommand(const std::string& cmd, std::string& cmdOutput)
{
	 char buffer[256];
	 std::fill(buffer, buffer + 256, 0);
	 std::stringstream sstr;
	 while (ssh_channel_is_open(channel_) && !ssh_channel_is_eof(channel_))
	 {
		 int nbytes = ssh_channel_read_nonblocking(channel_, buffer, sizeof(buffer), 0);
		 if (nbytes < 0)
		 {
		    TRACE_WARNING("Error read channel error, error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
			return false;
		 }
		 if (nbytes > 0)
		 {
			 sstr << std::string(buffer, nbytes);
		 }

         unsigned int nwritten = ssh_channel_write(channel_, cmd.c_str(), cmd.size());
		 if (nwritten != cmd.size())
		 {
			TRACE_WARNING("Error write channel error, error info:" << ssh_get_error(ssh_channel_get_session(channel_))); 
			 return false;
		 }
	 }
     cmdOutput = sstr.str();
	 return true;
}

}
