#include "parserTester.hpp"

static void	testOnlyCmd()
{
	std::vector<std::string>	in = split("PART");
	try
	{
		Part	cmd(in);
		printError("tests/test_Part.cpp:9:0 should throw an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndUser()
{
	std::vector<std::string>	in = split("PART robxxt");
	try
	{
		Part	cmd(in);
		printError("tests/test_Part.cpp:20:0 should throw an exception");
	}
	catch(std::exception& e) {}
}

static void	testCmdAndChannel()
{
	std::vector<std::string>	in = split("PART #school");
	try
	{
		Part	cmd(in);
	}
	catch(std::exception& e) 
	{
		printError("tests/test_Part.cpp:34:0 shouldn't throw an exception");
	}
}

static void	testCmdAndMessage()
{
	std::vector<std::string>	in = split("PART :hello world");
	try
	{
		Part	cmd(in);
		printError("tests/test_Part.cpp:44:0 should throw an exception");
	}
	catch(std::exception& e) {}
}

static void	testUserAndReasson()
{
	std::vector<std::string>	in = split("PART robxxt :hello world");
	try
	{
		Part	cmd(in);
		printError("tests/test_Part.cpp:55:0 should throw an exception");
	}
	catch(std::exception& e) {}
}

static void	testValidCmdAndChannelTrue()
{
	std::vector<std::string>	in = split("PART #school :hello world");
	try
	{
		Part	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "school", "tests/test_Part.cpp:66:0 => Part has not a channel called 'school'");
		ASSERT_EQUAL(cmd.getReasson(), "hello world", "tests/test_Part.cpp:67:0 => Part has not read properly the reasson");
	}
	catch(std::exception& e)
	{
		printError("tests/test_Part.cpp:71:0 should throw not throw an exception");
	}
}

static void	testEmptyMessage()
{
	std::vector<std::string>	in = split("PART #school :");
	try
	{
		Part	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "school", "tests/test_Part.cpp:81:0 => Part has not a channel called 'school'");
		ASSERT_EQUAL(cmd.getReasson(), "", "tests/test_Part.cpp:82:0 => Part has not read properly the reasson");
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		printError("tests/test_Part.cpp:86:0 shouldn't throw an exception");
	}
}

void	test_Part()
{
	testOnlyCmd();
	testCmdAndUser();
	testCmdAndChannel();
	testCmdAndMessage();
	testUserAndReasson();
	testValidCmdAndChannelTrue();
	testEmptyMessage();
}
