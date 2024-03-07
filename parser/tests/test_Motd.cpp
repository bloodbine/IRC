#include "parserTester.hpp"

static void	testSingleCommand()
{
	try
	{
		std::vector<std::string>	in = split("MOTD");
		Motd	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "", "tests/test_Motd.cpp:9:0 => channel should be empty");
	} catch (std::exception& e)
	{
		printError("tests/test_Motd.cpp:12:0 => failed to create Motd object");
	}
}

static void	testWithValidChannel()
{
	try
	{
		std::vector<std::string>	in = split("MOTD #school");
		Motd	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "school", "tests/test_Motd.cpp:23:0 => channel has the wrong value");
	} catch (std::exception& e)
	{
		printError("tests/test_Motd.cpp:25:0 => failed to create Motd object");
	}
}

static void	testWithInvalidChannel()
{
	try
	{
		std::vector<std::string>	in = split("MOTD channel");
		Motd	cmd(in);
		printError("tests/test_Motd.cpp:35:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithValidMode()
{
	try
	{
		std::vector<std::string>	in = split("MOTD #channel o");
		Motd	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Motd.cpp:45:0 => channel has the wrong value");
		printError("tests/test_Motd.cpp:46:0 => Should throw exception");
	} catch (std::exception& e)
	{
	}
}

static void	testWithInvalidLengthMode()
{
	try
	{
		std::vector<std::string>	in = split("MOTD #channel ola");
		Motd	cmd(in);
		printError("tests/test_Motd.cpp:58:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithInvalidMode()
{
	try
	{
		std::vector<std::string>	in = split("MOTD #channel b");
		Motd	cmd(in);
		printError("tests/test_Motd.cpp:68:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithInvalidArguments()
{
	try
	{
		std::vector<std::string>	in = split("MOTD #channel o b");
		Motd	cmd(in);
		printError("tests/test_Motd.cpp:78:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_Motd()
{
	testSingleCommand();
	testWithValidChannel();
	testWithInvalidChannel();
	testWithValidMode();
	testWithInvalidLengthMode();
	testWithInvalidMode();
	testWithInvalidArguments();
}
