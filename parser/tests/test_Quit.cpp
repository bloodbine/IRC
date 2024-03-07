#include "parserTester.hpp"

static void	testOnlyCmd()
{
	std::vector<std::string>	in = split("QUIT");
	try
	{
		Quit	cmd(in);
	}
	catch(std::exception& e)
	{
		printError("tests/test_Quit:9:0 => should not throw an exception");
	}
}

static void	testCmdWithMessage()
{
	std::vector<std::string>	in = split("QUIT :hello world");
	try
	{
		Quit	cmd(in);
		ASSERT_EQUAL(cmd.getMessage(), "hello world", "tests/test_Quit:20:0 => Quit has not read properly the message");
	}
	catch(std::exception& e)
	{
		printError("tests/test_Quit:24:0 should not throw an exception");
	}
}



static void	testInvalid()
{
	std::vector<std::string>	in = split("QUIT #school");
	try
	{
		Quit	cmd(in);
		printError("tests/test_Quit:36:0 should throw throw an exception");
	}
	catch(std::exception& e) {}
}

static void	testEmptyMsg()
{
	std::vector<std::string>	in = split("QUIT :");
	try
	{
		Quit	cmd(in);
		ASSERT_EQUAL(cmd.getMessage(), "", "tests/test_Quit:47:0 => Quit has not read properly the message");
	}
	catch(std::exception& e)
	{
		printError("tests/test_Quit:50:0 shouldn't throw throw an exception");
	}
}

static void	testInvalidOrder()
{
	std::vector<std::string>	in = split("QUIT hola :mundo");
	try
	{
		Quit	cmd(in);
		printError("tests/test_Quit:61:0 should throw throw an exception");
	}
	catch(std::exception& e)
	{
	}
}


void	test_Quit()
{
	testOnlyCmd();
	testCmdWithMessage();
	testInvalid();
	testEmptyMsg();
	testInvalidOrder();
}
