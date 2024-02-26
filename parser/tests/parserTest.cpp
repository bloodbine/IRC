#include "parserTest.hpp"

void	runTests()
{
	std::cout << "RUNNING TESTS..." << std::endl;
	compare(1, 2);
	compare("1", "2");
	compare("1", "1");
	compare(1, 1);
}
