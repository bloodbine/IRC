#include "parserTester.hpp"

static void	testOnlyCmd()
{
	std::vector<std::string>	in = split("PRIVMSG");
	try
	{
		Privmsg	cmd(in);
		printError("testOnlyCmd() should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndUser()
{
	std::vector<std::string>	in = split("PRIVMSG robxxt");
	try
	{
		Privmsg	cmd(in);
		printError("testCmdAndUser() should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndChannel()
{
	std::vector<std::string>	in = split("PRIVMSG #school");
	try
	{
		Privmsg	cmd(in);
		printError("testCmdAndChannel() should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndMessage()
{
	std::vector<std::string>	in = split("PRIVMSG :hello world");
	try
	{
		Privmsg	cmd(in);
		printError("testCmdAndMessage() should an exception");
	}
	catch(std::exception& e) {}
}

static void	testValidCmdAndUserTrue()
{
	std::vector<std::string>	in = split("PRIVMSG robxxt :hello world");
	try
	{
		Privmsg	cmd(in);
		ASSERT_EQUAL(cmd.getTarget(), "robxxt", "testValidCmdAndUserTrue() => Privmsg has not a target called 'robxxt'");
		ASSERT_EQUAL(cmd.getMessage(), "hello world", "testValidCmdAndUserTrue() => Privmsg has not read properly the message");
		ASSERT_EQUAL(cmd.getHasUser(), true, "testValidCmdAndUserTrue() => Privmsg has not set properly _hasUser");
	}
	catch(std::exception& e)
	{
		printError("testValidCmdAndUserTrue() should not throw an exception");
	}
}

static void	testValidCmdAndChannelTrue()
{
	std::vector<std::string>	in = split("PRIVMSG #school :hello world");
	try
	{
		Privmsg	cmd(in);
		ASSERT_EQUAL(cmd.getTarget(), "school", "testValidCmdAndChannelTrue() => Privmsg has not a target called 'school'");
		ASSERT_EQUAL(cmd.getMessage(), "hello world", "testValidCmdAndChannelTrue() => Privmsg has not read properly the message");
		ASSERT_EQUAL(cmd.getHasUser(), false, "testValidCmdAndChannelTrue() => Privmsg has not set properly _hasUser");
	}
	catch(std::exception& e)
	{
		printError("testValidCmdAndChannelTrue() should not throw an exception");
	}
}

static void	testEmptyMessage()
{
	std::vector<std::string>	in = split("PRIVMSG #school :");
	try
	{
		Privmsg	cmd(in);
		printError("testEmptyMessage() should throw an exception");
	}
	catch(std::exception& e)
	{
	}
}

void	test_Privmsg()
{
	testOnlyCmd();
	testCmdAndUser();
	testCmdAndChannel();
	testCmdAndMessage();
	testValidCmdAndUserTrue();
	testValidCmdAndChannelTrue();
	testEmptyMessage();
}
