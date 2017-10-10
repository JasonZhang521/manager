#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Environment.h"
#include "ShellCommandThread.h"
#include "ShellCommandOutputParse.h"
#include "ShellCommandPsTopnCpuUsageOutput.h"
#include "ShellCommandPsTopnMemoryUsageOutput.h"
#include "ShellCommandDfOutput.h"
#include "LoopMain.h"
#include <thread>
#include <iostream>

#ifdef WIN32
#else
#include <unistd.h>
#endif
using namespace Environment;

class EnvironmentTest : public ::testing::Test
{
};

#ifdef WIN32
#else
static void loopControl()
{
	Core::LoopMain::instance().loopStart();
}
TEST_F(EnvironmentTest, CommandTestDf)
{
	Environment::Environment env;
    IShellCommand* command = new ShellCommandThread(ShellCommand::getCmdString(ShellCommandType::DiskUsageDf), 1000);
	env.registerShellCmd(ShellCommandType::DiskUsageDf, command);
	std::thread th(loopControl);
	while(1)
	{
		const CommandOutputString& strings = env.getShellCmdOutput(ShellCommandType::DiskUsageDf);
		if (strings.empty())
		{
			sleep(1);
			continue;
		}
		for (auto str : strings)
		{
			std::cout << str << std::endl;
		}
	    ShellCommandDfOutputs dfOutputs;
	    ShellCommandOutputParse::ParseDfOutput(strings, dfOutputs);
		for (auto output : dfOutputs)
		{
			std::cout << "-------------------------------------" << std::endl;
			std::cout << output << std::endl;
			std::cout << "-------------------------------------" << std::endl;
		}
		break;
	}
    sleep(2);	
    command->stop();
	Core::LoopMain::instance().loopStop();
	th.join();
}

TEST_F(EnvironmentTest, CommandTestDuHome)
{
	Environment::Environment env;
    IShellCommand* command = new ShellCommandThread(ShellCommand::getCmdString(ShellCommandType::DiskUsageDuHome), 1000);
	env.registerShellCmd(ShellCommandType::DiskUsageDuHome, command);
	std::thread th(loopControl);
	while(1)
	{
		const CommandOutputString& strings = env.getShellCmdOutput(ShellCommandType::DiskUsageDuHome);
		if (strings.empty())
		{
			sleep(1);
			continue;
		}
		for (auto str : strings)
		{
			std::cout << str << std::endl;
		}
		uint64_t used = 0;
	    ShellCommandOutputParse::ParseDuHomeOutput(strings, used);
		{
			std::cout << "-------------------------------------" << std::endl;
			std::cout << used << std::endl;
			std::cout << "-------------------------------------" << std::endl;
		}
		break;
	}
    sleep(2);	
    command->stop();
	Core::LoopMain::instance().loopStop();
	th.join();
}

TEST_F(EnvironmentTest, CommandTestTop10CpuUsage)
{
	Environment::Environment env;
    IShellCommand* command = new ShellCommandThread(ShellCommand::getCmdString(ShellCommandType::PsTop10CpuUsage), 1000);
	env.registerShellCmd(ShellCommandType::PsTop10CpuUsage, command);
	std::thread th(loopControl);
	while(1)
	{
		const CommandOutputString& strings = env.getShellCmdOutput(ShellCommandType::PsTop10CpuUsage);
		if (strings.empty())
		{
			sleep(1);
			continue;
		}
		for (auto str : strings)
		{
			std::cout << str << std::endl;
		}
		ShellCommandPsTopnCpuUsageOutputs outputs;
	    ShellCommandOutputParse::ParsePsTopnCpuUsageOutput(strings, outputs);
		for (auto output : outputs)
		{
			std::cout << "-------------------------------------" << std::endl;
			std::cout << output << std::endl;
			std::cout << "-------------------------------------" << std::endl;
		}
		break;
	}
    sleep(2);	
    command->stop();
	Core::LoopMain::instance().loopStop();
	th.join();
}

TEST_F(EnvironmentTest, CommandTestTop10MemoryUsage)
{
	Environment::Environment env;
    IShellCommand* command = new ShellCommandThread(ShellCommand::getCmdString(ShellCommandType::PsTop10MemoryUsage), 1000);
	env.registerShellCmd(ShellCommandType::PsTop10MemoryUsage, command);
	std::thread th(loopControl);
	while(1)
	{
		const CommandOutputString& strings = env.getShellCmdOutput(ShellCommandType::PsTop10MemoryUsage);
		if (strings.empty())
		{
			sleep(1);
			continue;
		}
		for (auto str : strings)
		{
			std::cout << str << std::endl;
		}
		ShellCommandPsTopnMemoryUsageOutputs outputs;
	    ShellCommandOutputParse::ParsePsTopnMemoryUsageOutput(strings, outputs);
		for (auto output : outputs)
		{
			std::cout << "-------------------------------------" << std::endl;
			std::cout << output << std::endl;
			std::cout << "-------------------------------------" << std::endl;
		}
		break;
	}
    sleep(2);	
    command->stop();
	Core::LoopMain::instance().loopStop();
	th.join();
}

#endif
