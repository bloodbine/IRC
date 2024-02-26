#include "parserTest.hpp"

void	testOneSplit(int caseNum, const std::vector<std::string>& out, const std::vector<std::string>& expect)
{
	if (compareVectors(out, expect) == 1)
	{
		std::cout << ANSI_BOLD << ANSI_RED << " <=== [ ERROR test_split() test " << caseNum << " ]" << ANSI_RESET << std::endl;
		std::cout << "out: ";
		printVector(out);
		std::cout << "expect: ";
		printVector(expect);
	}
}

void	test1()
{
	std::vector<std::string>	v1;
	v1.push_back("Hola");
	v1.push_back("mundo");
	std::vector<std::string>	o1 = split("Hola mundo");

	testOneSplit(1, o1, v1);
}

void	test2()
{
	std::vector<std::string>	v1;
	v1.push_back("Hola");
	std::vector<std::string>	o1 = split("Hola");

	testOneSplit(2, o1, v1);
}

void	test3()
{
	std::vector<std::string>	v1;
	v1.push_back("");
	std::vector<std::string>	o1 = split("");

	testOneSplit(3, o1, v1);
}

void	test_split() {
	test1();
	test2();
	test3();
}
