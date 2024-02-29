#include "parserTester.hpp"

static void	testEmptySplit()
{
	std::vector<std::string>	actual = split("");
	std::vector<std::string>	expected;

	ASSERT_EQUAL(actual.size(), expected.size(), "testEmptySplit() => The sizes of the vectors are different!");
}

static void	testOneItemSplit()
{
	std::vector<std::string>	actual = split("Hola");
	std::vector<std::string>	expected;

	expected.push_back("Hola");
	ASSERT_EQUAL(actual.size(), expected.size(), "testOneItemSplit() => The sizes of the vectors are different!");
	ASSERT_EQUAL(actual[0], expected[0], "testOneItemSplit() => The element 0 is different!");
}

static void	testTwoItemSplit()
{
	std::vector<std::string>	actual = split("Hola mundo");
	std::vector<std::string>	expected;

	expected.push_back("Hola");
	expected.push_back("mundo");
	ASSERT_EQUAL(actual.size(), expected.size(), "testTwoItemSplit() => The sizes of the vectors are different!");
	ASSERT_EQUAL(actual[0], expected[0], "testTwoItemSplit() => The element 0 is different!");
	ASSERT_EQUAL(actual[1], expected[1], "testTwoItemSplit() => The element 0 is different!");
}

void	test_split()
{
	testEmptySplit();
	testOneItemSplit();
	testTwoItemSplit();
}
