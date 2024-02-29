#include "parserTester.hpp"

static void	testInvalidAmountArguments()
{
	std::vector<std::string> in	= split("PING hola");
	try
	{
		Ping	cmd(in);
		printError("tests/test_Ping.cpp:9:0 should throw an exception");
	} catch (std::exception& e) {}
}

static void	testValidPing()
{
	std::vector<std::string> in	= split("PING");
	try
	{
		Ping	cmd(in);
	} catch (std::exception& e) { printError("tests/test_Ping.cpp:19:0 should build the Ping object"); }
}

void	test_Ping()
{
	testInvalidAmountArguments();
	testValidPing();
}