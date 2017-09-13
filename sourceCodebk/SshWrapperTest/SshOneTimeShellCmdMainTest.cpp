#include "SshClient.h"
#include "SshClientSession.h"
#include "SshShellChannel.h"
#include <SshConfigure.h>
#include "libssh/libssh.h"
#include <iostream>
#include <string>
using namespace SshWrapper;
int main()
{
    std::string user, password, hostname;
    // std::cout << "Input host:";
    // std::cin >> hostname;
    hostname = "selnpcgwnx1000.seln.ete.ericsson.se";
    std::cout << "Input User:";
    std::cin >> user;
    std::cout << "Input password:";
    std::cin >> password;
    std::cout << "start" << std::endl;
	SshConfigure configure;
    configure.user = user;
    configure.password = password;
    configure.host = "selnpcgwnx1000.seln.ete.ericsson.se";
	configure.port = 22;
	configure.verbosity = SSH_LOG_PROTOCOL;
	configure.unknownHostContinue = true;
	ssh_session session = ssh_new();
	SshShellChannel* channel = new SshShellChannel(session);
	SshClientSession* clientSession = new SshClientSession(session, channel, configure);
	ISshClient* client = new SshClient(clientSession);
	client->setup();
	std::string inputString;
	std::string outputString;
	client->startShell();
	while (inputString != std::string("exit"))
	{
		char ch[256];
		std::fill(ch, ch + 256, 0);
		std::cout << "Input command:";
		std::cin.getline(ch, 255);
		std::cout << "[" << ch << "]" << std::endl;
		inputString = ch;
        client->executeShellCommand(inputString, outputString);
		std::cout << outputString << std::endl;
	}
    client->shutdownShell();
	client->shutdown();
	return 0;
}
