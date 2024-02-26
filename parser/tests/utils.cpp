#include "parserTest.hpp"

void	printError(const std::string& func, int caseNum)
{
	std::cout << ANSI_BOLD << ANSI_RED << " <=== [ ERROR " << func << "() test " << caseNum << " ]" << ANSI_RESET << std::endl;
}