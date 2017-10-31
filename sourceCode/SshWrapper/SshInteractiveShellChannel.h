#ifndef _SSHWRAPPER_SSHINTERACTIVESHELLCHANNEL_H_
#define _SSHWRAPPER_SSHINTERACTIVESHELLCHANNEL_H_
#include "ISshShellChannel.h"
#include "Component.h"
#include "Macro.h"

struct ssh_session_struct;
struct ssh_channel_struct;
typedef struct ssh_channel_struct* ssh_channel;
typedef struct ssh_session_struct* ssh_session;
namespace SshWrapper
{

class SshInteractiveShellChannel : public ISshShellChannel
{
	ssh_session session_;
	ssh_channel channel_;
	int cols_;
	int rows_;
public:
	SshInteractiveShellChannel(ssh_session session, int cols, int rows);
protected:
	~SshInteractiveShellChannel();
	virtual bool setup();
	virtual bool shutdown();
	virtual bool executeCommand(const std::string& cmd, std::string& cmdOutput);
private:
	bool sessionAndTerminalInit();
    bool interactive();
    /*
    bool interactive2(const std::string& cmd);
    void selectLoop();
    */

public:
     GETCLASSNAME(SshInteractiveShellChannel)
};

}
#endif
