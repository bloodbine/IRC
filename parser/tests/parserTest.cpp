#include "parserTest.hpp"

void	runTests()
{
	std::cout << ANSI_BOLD << ANSI_GREEN <<"\t\t\t\tRUNNING TESTS..." << ANSI_RESET << std::endl;
	test_split();
	test_isValidPrivmsg();
	test_Privmsg();
	test_Pass();
	test_Whois();
}
