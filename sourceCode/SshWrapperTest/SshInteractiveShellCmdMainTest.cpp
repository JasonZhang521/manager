#include "SshClient.h"
#include "SshClientSession.h"
#include "SshInteractiveShellChannel.h"
#include "SshConfigure.h"
#include "libssh/libssh.h"
#include <iostream>
#include <string>
using namespace SshWrapper;;
int main()
{
    std::string user, password, hostname;
    hostname = "192.168.5.138";
    //std::cout << "Input User:";
    //std::cin >> user;
    //std::cout << "Input password:";
    //std::cin >> password;
    //std::cout << "start" << std::endl;

    SshConfigure configure;
    configure.user = "test";
    configure.password = "test";
    configure.host = "192.168.5.138";
	configure.port = 22;
    // configure.verbosity = SSH_LOG_PROTOCOL;
    configure.verbosity = SSH_LOG_WARNING;
	configure.unknownHostContinue = true;
	ssh_session session = ssh_new();
	SshInteractiveShellChannel* channel = new SshInteractiveShellChannel(session, 80, 80);
	SshClientSession* clientSession = new SshClientSession(session, channel, configure);
	ISshClient* client = new SshClient(clientSession);
	client->setup();
	std::string inputString;
	std::string outputString;
	client->startShell();
    client->executeShellCommand(std::string("ls -a"), outputString);
    //client->executeShellCommand(inputString, outputString);
/*
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
*/
    std::cout << outputString << std::endl;
    client->shutdownShell();
	client->shutdown();
	return 0;
}
