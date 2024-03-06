#include "parserTester.hpp"

static void	testOnlyCmd()
{
	std::vector<std::string>	in = split("TOPIC");
	try
	{
		Topic	cmd(in);
		printError("tests/test_Topic.cpp:9:0 should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndUser()
{
	std::vector<std::string>	in = split("TOPIC robxxt");
	try
	{
		Topic	cmd(in);
		printError("tests/test_Topic.cpp:20:0 should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndChannel()
{
	std::vector<std::string>	in = split("TOPIC #school");
	try
	{
		Topic	cmd(in);
		printError("tests/test_Topic.cpp:31:0 should an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndMessage()
{
	std::vector<std::string>	in = split("TOPIC :hello world");
	try
	{
		Topic	cmd(in);
		printError("tests/test_Topic.cpp:42:0 should an exception");
	}
	catch(std::exception& e) {}
}

static void	testValidCmdAndUserTrue()
{
	std::vector<std::string>	in = split("TOPIC robxxt :hello world");
	try
	{
		Topic	cmd(in);
		ASSERT_EQUAL(cmd.getTarget(), "robxxt", "tests/test_Topic.cpp:53:0 => Topic has not a target called 'robxxt'");
		ASSERT_EQUAL(cmd.getMessage(), "hello world", "tests/test_Topic.cpp:54:0 => Topic has not read properly the message");
		printError("tests/test_Topic.cpp:55:0 should throw an exception");
	}
	catch(std::exception& e)
	{
	}
}

static void	testValidCmdAndChannelTrue()
{
	std::vector<std::string>	in = split("TOPIC #school :hello world");
	try
	{
		Topic	cmd(in);
		ASSERT_EQUAL(cmd.getTarget(), "school", "tests/test_Topic.cpp:68:0 => Privmsg has not a target called 'school'");
		ASSERT_EQUAL(cmd.getMessage(), "hello world", "tests/test_Topic.cpp:69:0 => Privmsg has not read properly the message");
	}
	catch(std::exception& e)
	{
		printError("tests/test_Topic.cpp:73:0 should not throw an exception");
	}
}

static void	testEmptyMessage()
{
	std::vector<std::string>	in = split("TOPIC #school :");
	try
	{
		Topic	cmd(in);
		printError("tests/test_Topic.cpp:83:0 should throw an exception");
	}
	catch(std::exception& e)
	{
	}
}

void	test_Topic()
{
	testOnlyCmd();
	testCmdAndUser();
	testCmdAndChannel();
	testCmdAndMessage();
	testValidCmdAndUserTrue();
	testValidCmdAndChannelTrue();
	testEmptyMessage();
}