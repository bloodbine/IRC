#include "parserTester.hpp"

void	testEmptySplit()
{
	std::vector<std::string>	actual = split("");
	std::vector<std::string>	expected;

	ASSERT_EQUAL(actual.size(), expected.size(), "testEmptySplit() => The sizes of the vectors are different!");
}

void	test_split()
{
	testEmptySplit();
}