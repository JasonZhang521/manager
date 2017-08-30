#ifndef _SSHWRAPPER_SSHSHELLCHANNEL_H_
#define _SSHWRAPPER_SSHSHELLCHANNEL_H_
#include "ISshShellChannel.h"
#include "Component.h"
#include "Macro.h"

struct ssh_session_struct;
struct ssh_channel_struct;
typedef struct ssh_channel_struct* ssh_channel;
typedef struct ssh_session_struct* ssh_session;
namespace SshWrapper
{

class SshShellChannel : public ISshShellChannel
{
	ssh_session session_;
	ssh_channel channel_;
public:
	SshShellChannel(ssh_session session);
protected:
	~SshShellChannel();
	virtual bool setup();
	virtual bool shutdown();
	virtual bool executeCommand(const std::string& cmd, std::string& cmdOutput);
private:
	bool startShellCmd();
	bool stopShellCmd();

public:
     GETCLASSNAME(SshShellChannel)
};

}
#endif
