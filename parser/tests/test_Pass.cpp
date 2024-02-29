#include "parserTester.hpp"

void	test_onlyPass()
{
	std::vector<std::string>	in = split("PASS");
	try
	{
		Pass	cmd(in);
		printError("test_onlyPass() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_tooLongPass()
{
	std::vector<std::string>	in = split("PASS testUserContainsDigitButNotAtStarttestUserContainsDigitButNotAtStart");
	try
	{
		Pass	cmd(in);
		printError("test_tooLongPass() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_tooShortPass()
{
	std::vector<std::string>	in = split("PASS 12");
	try
	{
		Pass	cmd(in);
		printError("test_tooShortPass() showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_incorrectArgumentsForPass()
{
	std::vector<std::string>	in = split("PASS hello world");
	try
	{
		Pass	cmd(in);
		printError("tests/test_Pass.cpp:42:0 => showld throw an exception");
	}
	catch(std::exception& e) {}
}

void	test_CorrectPass()
{
	std::vector<std::string>	in = split("PASS 1234");
	Pass						cmd(in);

	ASSERT_EQUAL(cmd.getPassword(), "1234", "tests/test_Pass.cpp:52:0 => Pass doesn't have saved the correct password.");
}

void	test_Pass()
{
	test_onlyPass();
	test_tooLongPass();
	test_tooShortPass();
	test_incorrectArgumentsForPass();
	test_CorrectPass();
}