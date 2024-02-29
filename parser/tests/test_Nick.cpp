#include "parserTester.hpp"

void	test_onlyNick()
{
	std::vector<std::string>	in = split("NICK");
	try
	{
		Nick	cmd(in);
		printError("test_onlyNick() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_tooLongNick()
{
	std::vector<std::string>	in = split("NICK testUserContainsDigitButNotAtStarttestUserContainsDigitButNotAtStart");
	try
	{
		Nick	cmd(in);
		printError("test_tooLongNick() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_tooShortNick()
{
	std::vector<std::string>	in = split("NICK 12");
	try
	{
		Nick	cmd(in);
		printError("test_tooShortNick() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_incorrectArgumentsForNick()
{
	std::vector<std::string>	in = split("NICK hello world");
	try
	{
		Nick	cmd(in);
		printError("tests/test_Nick.cpp:42:0 => showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_CorrectNick()
{
	std::vector<std::string>	in = split("NICK 1234");
	Nick						cmd(in);

	ASSERT_EQUAL(cmd.getUser(), "1234", "tests/test_Nick.cpp:52:0 => Pass doesn't have saved the correct password.");
}

void	test_Nick()
{
	test_onlyNick();
	test_tooLongNick();
	test_tooShortNick();
	test_incorrectArgumentsForNick();
	test_CorrectNick();
}