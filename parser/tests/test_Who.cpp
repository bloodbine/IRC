#include "parserTester.hpp"

static void	testSingleCommand()
{
	try
	{
		std::vector<std::string>	in = split("WHO");
		Who	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "", "tests/test_Who.cpp:9:0 => channel should be empty");
		ASSERT_EQUAL(cmd.getQueryOperator(), false, "tests/test_Who.cpp:10:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Who.cpp:13:0 => failed to create Who object");
	}
}

static void	testWithValidChannel()
{
	try
	{
		std::vector<std::string>	in = split("WHO #school");
		Who	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "school", "tests/test_Who.cpp:23:0 => channel has the wrong value");
		ASSERT_EQUAL(cmd.getQueryOperator(), false, "tests/test_Who.cpp:24:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Who.cpp:27:0 => failed to create Who object");
	}
}

static void	testWithInvalidChannel()
{
	try
	{
		std::vector<std::string>	in = split("WHO channel");
		Who	cmd(in);
		printError("tests/test_Who.cpp:37:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithValidMode()
{
	try
	{
		std::vector<std::string>	in = split("WHO #channel o");
		Who	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Who.cpp:47:0 => channel has the wrong value");
		ASSERT_EQUAL(cmd.getQueryOperator(), true, "tests/test_Who.cpp:48:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Who.cpp:51:0 => failed to create Who object");
	}
}

static void	testWithInvalidLengthMode()
{
	try
	{
		std::vector<std::string>	in = split("WHO #channel ola");
		Who	cmd(in);
		printError("tests/test_Who.cpp:61:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithInvalidMode()
{
	try
	{
		std::vector<std::string>	in = split("WHO #channel b");
		Who	cmd(in);
		printError("tests/test_Who.cpp:71:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithInvalidArguments()
{
	try
	{
		std::vector<std::string>	in = split("WHO #channel o b");
		Who	cmd(in);
		printError("tests/test_Who.cpp:81:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_Who()
{
	testSingleCommand();
	testWithValidChannel();
	testWithInvalidChannel();
	testWithValidMode();
	testWithInvalidLengthMode();
	testWithInvalidMode();
	testWithInvalidArguments();
}
