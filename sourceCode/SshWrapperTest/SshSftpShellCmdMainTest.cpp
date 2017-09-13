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


bool parseFileNameFromCommond(size_t pos, const std::string& inputCommand, std::string& fileName)
{
    size_t startPos = pos;
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
    configure.user = "test";
    configure.password = "test";
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
              << "(3) [get file]: download file\n"
              << "(4) [getc file]: download file continue\n"
              << "(5) [mv srcFile dstFile]: mv srcFile dstFile\n" << std::endl;

	std::string inputString;
	while (inputString != std::string("exit"))
	{
        char ch[256];
        std::fill(ch, ch + 256, 0);
		std::cout << "Input command:";
		std::cin.getline(ch, 255);
        if (ch[0] == 0)
        {
            continue;
        }
		std::cout << "[" << ch << "]" << std::endl;
		inputString = ch;
        bool isError = false;
		if (inputString == std::string("ls"))
		{
	        SftpDirAttributes attributes;
            isError = !client->listDir(std::string("."), attributes);
	        std::cout << attributes << std::endl;
		}
        if (inputString.substr(0, 3) == std::string("lsf"))
        {
            std::string remotefile;
            if (parseFileNameFromCommond(3, inputString, remotefile))
            {
                std::cout << "execute cmd lsf:" << remotefile << std::endl;
                SftpFileAttribute attribute;
                std::cout << "list file:" << remotefile << std::endl;
                isError = !client->listRemoteFileAttribute(remotefile, attribute);
                std::cout << attribute << std::endl;
            }
            else
            {
                isError = true;
            }
        }
        else if(inputString.substr(0, 4) == std::string("getc") && inputString.size() > 5)
        {
            std::string downFile;
            if (parseFileNameFromCommond(4, inputString, downFile))
            {
                std::cout << "download file:" << downFile << std::endl;
                isError = !client->getFileFromLastPos(downFile, downFile);
            }
            else
            {
                isError = true;
            }
            std::cout << "end download file:" << downFile << std::endl;
        }
        else if(inputString.substr(0, 3) == std::string("get") && inputString.size() > 4)
		{
            std::string downFile;
            if (parseFileNameFromCommond(3, inputString, downFile))
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
            if (parseFileNameFromCommond(3, inputString, upFile))
            {
                std::cout << "inputString:" << inputString << ", uploadFile: " << upFile << std::endl;
                isError = !client->putFile(upFile, ".");
            }
            else
            {
                isError = true;
            }
        }
        else if (inputString.substr(0, 2) == std::string("mv") && inputString.size() > 5)
        {

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
                      << "(3) [get file]: download file\n"
                      << "(4) [getc file]: download file continue\n"
                      << std::endl;
        }
	}
    //client->putFile()
    client->shutdownSftp();
    client->shutdown();
    return 0;
}
