#include "SshClient.h"
#include "SshClientSession.h"
#include "SshShellChannel.h"
#include "SshFtpSession.h"
#include <SshConfigure.h>
#include "SftpDirAttribute.h"
#include "libssh/libssh.h"
#include <iostream>
#include <string>

using namespace SshWrapper;


bool parseFileNameFromCommond(const std::string& inputCommand, std::string& fileName)
{
    size_t startPos = 3;
    if (inputCommand[startPos] != ' ')
    {
        return false;
    }
    else
    {
        while (inputCommand[startPos] == ' ' && startPos < inputCommand.size())
        {
            ++startPos;
        }

        if (startPos >= inputCommand.size())
        {
            return false;
        }
    }

    size_t endPos = inputCommand.size() - 1;
    while (inputCommand[endPos] == ' ' && endPos >= startPos)
    {
        --endPos;
    }

    if (endPos < startPos)
    {
        return false;
    }
    else
    {
        fileName = inputCommand.substr(startPos, endPos - startPos + 1);
    }

    return true;
}

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    std::string user, password, hostname;
    // std::cout << "Input host:";
    // std::cin >> hostname;
    hostname = "192.168.5.138";
    std::cout << "Input User:";
    std::cin >> user;
    std::cout << "Input password:";
    std::cin >> password;
    std::cout << "start" << std::endl;
    SshConfigure configure;
    configure.user = user;
    configure.password = password;
    configure.host = hostname;
    configure.port = 22;
    configure.verbosity = SSH_LOG_NOLOG; //SSH_LOG_PROTOCOL;
    configure.unknownHostContinue = true;
    ssh_session session = ssh_new();
    std::cout << "step 1" << std::endl;
    SshClientSession* clientSession = new SshClientSession(session, configure);
    std::cout << "step 2" << std::endl;
    ISshClient* client = new SshClient(clientSession);
    std::cout << "step 4" << std::endl;
    client->setup();
    client->startSftp();
    std::cout << "Input cmd:\n"
              << "(1) [ls]: list the Dir\n"
              << "(2) [put file]: upload file\n"
              << "(3) [get file]: download file\n";

	std::string inputString;
	while (inputString != std::string("exit"))
	{
        char ch[256];
        std::fill(ch, ch + 256, 0);
		std::cout << "Input command:";
		std::cin.getline(ch, 255);
		std::cout << "[" << ch << "]" << std::endl;
		inputString = ch;
        bool isError = false;
		if (inputString == std::string("ls"))
		{
	        SftpDirAttributes attributes;
            isError = !client->listDir(std::string("."), attributes);
	        std::cout << attributes << std::endl;
		}
        else if(inputString.substr(0, 3) == std::string("get") && inputString.size() > 4)
		{
            std::string downFile;
            if (parseFileNameFromCommond(inputString, downFile))
            {
                isError = !client->getFile(downFile, ".");
            }
            else
            {
                isError = true;
            }
		}
        else if (inputString.substr(0, 3) == std::string("put") && inputString.size() > 4)
		{
            std::string upFile;
            if (parseFileNameFromCommond(inputString, upFile))
            {
                std::cout << "inputString:" << inputString << ", uploadFile: " << upFile << std::endl;
                isError = !client->putFile(upFile, ".");
            }
            else
            {
                isError = true;
            }
        }
        else
        {
            isError = true;
        }

        if (isError)
        {
            std::cout << "Command Error" << std::endl;
            std::cout << "Input cmd:\n"
                      << "(1) [ls]: list the Dir\n"
                      << "(2) [put file]: upload file\n"
                      << "(3) [get file]: download file"
                      << std::endl;
        }
	}
    //client->putFile()
    client->shutdownSftp();
    client->shutdown();
    return 0;
}
