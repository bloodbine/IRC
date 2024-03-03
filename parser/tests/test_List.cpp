#include "parserTester.hpp"

static void	testSingleCommand()
{
	try
	{
		std::vector<std::string>	in = split("LIST");
		List	cmd(in);
		ASSERT_EQUAL(cmd.getChannelExists(), false, "tests/test_List.cpp:9:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_List.cpp:12:0 => failed to create List object");
	}
}

static void	testWithValidChannel()
{
	try
	{
		std::vector<std::string>	in = split("LIST #school");
		List	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "school", "tests/test_List.cpp:21:0 => channel has the wrong value");
		ASSERT_EQUAL(cmd.getChannelExists(), true, "tests/test_List.cpp:22:0 => queryOperator should be true");
	} catch (std::exception& e)
	{
		printError("tests/test_List.cpp:26:0 => failed to create List object");
	}
}

static void	testWithInvalidChannel()
{
	try
	{
		std::vector<std::string>	in = split("LIST channel");
		List	cmd(in);
		printError("tests/test_List.cpp:36:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	testWithInvalidLengthMode()
{
	try
	{
		std::vector<std::string>	in = split("LIST #channel ola");
		List	cmd(in);
		printError("tests/test_List.cpp:46:0 => should throw an exception");
	} catch (std::exception& e) {}
}


static void	testWithInvalidArguments()
{
	try
	{
		std::vector<std::string>	in = split("LIST #channel o b");
		List	cmd(in);
		printError("tests/test_List.cpp:57:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_List()
{
	testSingleCommand();
	testWithValidChannel();
	testWithInvalidChannel();
	testWithInvalidLengthMode();
	testWithInvalidArguments();
}
