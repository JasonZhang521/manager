#ifndef _SSH_CLIENT_H_
#define _SSH_CLIENT_H_
#include "Component.h"
#include "Macro.h"
#include <map>
struct ssh_session_struct;
typedef struct ssh_session_struct* ssh_session;
typedef std::map<int, void*> OptionsMap;

class SshClient
{
	ssh_session session_;
	bool unknownHostContinue_;
	std::string user_;
	std::string password_;
	std::string host_;
	int verbosity_;
	int port_;
	ssh_channel cliChannel_;
public:
	explicit SshClient(bool unknownHostContinue, const std::string& user,
			const std::string& password, const std::string& host, int verbosity, int port);
	~SshClient();
	bool setup();
	void shutdown();
	void setOptions(const OptionsMap& options);
	bool executeCliCommand(const std::string& cli, std::string& cliResult);
private:
	void setDefaultOptions();
	bool connect();
	void disconnect();
	bool verifyKnownhost();
	bool verifyUser();
	bool openCliChannel();
    void closeCliChannel();
public:	
     GETCLASSNAME(SshClientSession)
};
#endif
