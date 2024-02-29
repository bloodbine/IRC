#include "parserTester.hpp"

void	testSingleCommand()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS");
		Whois	cmd(in);
		ASSERT_EQUAL(cmd.getUser(), "", "tests/test_Whois.cpp:9:0 => user should be empty");
		ASSERT_EQUAL(cmd.getQueryOperator(), false, "tests/test_Whois.cpp:10:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Whois.cpp:13:0 => failed to create Whois object");
	}
}

void	testWithValidUser()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS username");
		Whois	cmd(in);
		ASSERT_EQUAL(cmd.getUser(), "username", "tests/test_Whois.cpp:23:0 => user has the wrong value");
		ASSERT_EQUAL(cmd.getQueryOperator(), false, "tests/test_Whois.cpp:24:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Whois.cpp:27:0 => failed to create Whois object");
	}
}

void	testWithInvalidUser()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS #username");
		Whois	cmd(in);
		printError("tests/test_Whois.cpp:37:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	testWithValidMode()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS username o");
		Whois	cmd(in);
		ASSERT_EQUAL(cmd.getUser(), "username", "tests/test_Whois.cpp:47:0 => user has the wrong value");
		ASSERT_EQUAL(cmd.getQueryOperator(), true, "tests/test_Whois.cpp:48:0 => queryOperator should be false");
	} catch (std::exception& e)
	{
		printError("tests/test_Whois.cpp:51:0 => failed to create Whois object");
	}
}

void	testWithInvalidLengthMode()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS username ola");
		Whois	cmd(in);
		printError("tests/test_Whois.cpp:61:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	testWithInvalidMode()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS username b");
		Whois	cmd(in);
		printError("tests/test_Whois.cpp:71:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	testWithInvalidArguments()
{
	try
	{
		std::vector<std::string>	in = split("WHOIS username o b");
		Whois	cmd(in);
		printError("tests/test_Whois.cpp:81:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_Whois()
{
	testSingleCommand();
	testWithValidUser();
	testWithInvalidUser();
	testWithValidMode();
	testWithInvalidLengthMode();
	testWithInvalidMode();
	testWithInvalidArguments();
}
