#include "SshInteractiveShellChannel.h"
#include <string>
#include <map>
#include <sstream>
#include <libssh/libssh.h>
#include "App.h"
#include "Trace.h"
#include <stdlib.h>

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

    if (!sessionAndTerminalInit())
    {
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
     std::string command(cmd);
     cmdOutput.clear();
	 char buffer[256];
	 std::fill(buffer, buffer + 256, 0);

     while (ssh_channel_is_open(channel_) && !ssh_channel_is_eof(channel_))
     {
        int nbytes = ssh_channel_read_nonblocking(channel_, buffer, sizeof(buffer), 0);

        while (nbytes > 0)
        {
           std::stringstream sstr;
           sstr.write(buffer, nbytes);
           cmdOutput += sstr.str();
           std::cout << sstr.str() << std::endl;
           nbytes = ssh_channel_read_nonblocking(channel_, buffer, sizeof(buffer), 0);
        }

        if (nbytes < 0)
        {
           TRACE_WARNING("Error read channel error, error info:" << ssh_get_error(ssh_channel_get_session(channel_)));
           return false;
        }

        if (!cmd.empty())
        {
            unsigned int nwritten = ssh_channel_write(channel_, cmd.c_str(), cmd.size());
            if (nwritten != cmd.size())
            {
               TRACE_WARNING("Error write channel error, error info:" << ssh_get_error(ssh_channel_get_session(channel_)));
                return false;
            }
            ssh_channel_write(channel_, "\n", 1);
            std::cout << "\n write command:" << cmd << "\n" << std::endl;
        }

        nbytes = ssh_channel_read_nonblocking(channel_, buffer, sizeof(buffer), 0);

        while (nbytes > 0)
        {
           std::stringstream sstr;
           sstr.write(buffer, nbytes);
           cmdOutput += sstr.str();
           std::cout << sstr.str() << std::endl;
           nbytes = ssh_channel_read_nonblocking(channel_, buffer, sizeof(buffer), 0);
        }

        if (nbytes < 0)
        {
           TRACE_WARNING("Error read channel error, error info:" << ssh_get_error(ssh_channel_get_session(channel_)));
           return false;
        }

        break;
     }

	 return true;
}

bool SshInteractiveShellChannel::interactive()
{
  char buffer[256];
  int nbytes, nwritten;
  ssh_channel_request_exec(channel_, "ls -a");
  while (ssh_channel_is_open(channel_) &&
         !ssh_channel_is_eof(channel_))
  {
    struct timeval timeout;
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);

    ssh_channel in_channels[2], out_channels[2];
    in_channels[0] = channel_;
    in_channels[1] = NULL;

    FD_SET(ssh_get_fd(session_), &fds);
    int maxfd = ssh_get_fd(session_) + 1;

    ssh_select(in_channels, out_channels, maxfd, &fds, &timeout);

    if (out_channels[0] != NULL)
    {
      nbytes = ssh_channel_read(channel_, buffer, sizeof(buffer), 0);
      std::cout << "read bytes from channel:" << nbytes << std::endl;
      if (nbytes < 0) return SSH_ERROR;
      if (nbytes > 0)
      {
        nwritten = write(1, buffer, nbytes);
        std::cout << "write bytes to 1:" << nbytes << std::endl;
        if (nwritten != nbytes) return SSH_ERROR;
      }
    }

    if (FD_ISSET(0, &fds))
    {
      nbytes = read(0, buffer, sizeof(buffer));
      std::cout << "read bytes from 0:" << nbytes << std::endl;
      if (nbytes < 0) return SSH_ERROR;
      if (nbytes > 0)
      {
        nwritten = ssh_channel_write(channel_, buffer, nbytes);
        std::cout << "write bytes to channel:" << nbytes << std::endl;
        if (nbytes != nwritten) return false;
      }
    }
  }

  return true;
}
/*
bool SshInteractiveShellChannel::interactive2(const std::string& cmd)
{
    ssh_channel_request_exec(channel_, cmd.c_str());
    selectLoop();
}

void SshInteractiveShellChannel::selectLoop()
{
    ssh_connector connector_in, connector_out, connector_err;
    ssh_event event = ssh_event_new();

    // stdin
    connector_in = ssh_connector_new(session_);
    ssh_connector_set_out_channel(connector_in, channel_, SSH_CONNECTOR_STDOUT);
    ssh_connector_set_in_fd(connector_in, 0);
    ssh_event_add_connector(event, connector_in);

    // stdout
    connector_out = ssh_connector_new(session_);
    ssh_connector_set_out_fd(connector_out, 1);
    ssh_connector_set_in_channel(connector_out, channel_, SSH_CONNECTOR_STDOUT);
    ssh_event_add_connector(event, connector_out);

    // stderr
    connector_err = ssh_connector_new(session_);
    ssh_connector_set_out_fd(connector_err, 2);
    ssh_connector_set_in_channel(connector_err, channel_, SSH_CONNECTOR_STDERR);
    ssh_event_add_connector(event, connector_err);

    while(ssh_channel_is_open(channel_))
    {

        //if(signal_delayed)
        //    sizechanged();

        ssh_event_dopoll(event, 60000);
    }
    ssh_event_remove_connector(event, connector_in);
    ssh_event_remove_connector(event, connector_out);
    ssh_event_remove_connector(event, connector_err);

    ssh_connector_free(connector_in);
    ssh_connector_free(connector_out);
    ssh_connector_free(connector_err);

    ssh_event_free(event);
}

*/

}
