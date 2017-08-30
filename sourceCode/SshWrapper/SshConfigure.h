#ifndef _SSHWRAPPER_SSHCONFIGURE_H_
#define _SSHWRAPPER_SSHCONFIGURE_H_
#include <string>
namespace SshWrapper
{

struct SshConfigure
{
	SshConfigure()
	:port(-1)
	,verbosity(-1)
	,unknownHostContinue(false)
	{}

	SshConfigure(const SshConfigure& config)
	:user(config.user)
	,password(config.password)
	,host(config.host)
	,port(config.port)
	,verbosity(config.verbosity)
	,unknownHostContinue(config.unknownHostContinue)
	{}

	SshConfigure& operator=(const SshConfigure& config)
	{
		user = config.user;
		password = config.password;
		host = config.host;
		port = config.port;
		verbosity = config.verbosity;
		unknownHostContinue = config.unknownHostContinue;
		return *this;
	}

	std::string user;
	std::string password;
	std::string host;
	int port;
	int verbosity;
	bool unknownHostContinue;
};

}
#endif
