#include "parserTest.hpp"


static void	test1()
{
	Pass			out("PASS 1234");
	std::string		expect = "1234";

	if (compare(out.getPassword(), expect) == false)
	{
		printError("test_Pass", 1);
	}
}

static void	test2()
{
	try
	{
		Pass			out("PASS");
		std::cerr << "Invalid number of arguments";
		printError("test_Pass", 2);
	} catch (std::exception& e) {}
}

static void	test3()
{
	try
	{
		Pass			out("PASS hola mundo");
		std::cerr << "Invalid number of arguments";
		printError("test_Pass", 2);
	} catch (std::exception& e) {}
}


void	test_Pass()
{
	test1();
	test2();
	test3();
}
