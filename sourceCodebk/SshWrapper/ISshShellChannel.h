#ifndef _SSHWRAPPER_ISSHSHELLCHANNEL_H_
#define _SSHWRAPPER_ISSHSHELLCHANNEL_H_
#include <string>

namespace SshWrapper
{

class ISshShellChannel
{
public:
	ISshShellChannel() {}
	virtual ~ISshShellChannel() {}

	virtual bool setup() = 0;
	virtual bool shutdown() = 0;
	virtual bool executeCommand(const std::string& cmd, std::string& cmdOutput) = 0;
};

}
#endif

