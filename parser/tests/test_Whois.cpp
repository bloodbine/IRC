#include "parserTest.hpp"


static void	test1()
{
	Whois			out("WHOIS 1234");
	std::string		expect = "1234";

	if (compare(out.getTarget(), expect) == false)
	{
		printError("test_Whois", 1);
	}
}

static void	test2()
{
	try
	{
		Whois			out("WHOIS");
		std::cerr << "Invalid number of arguments";
		printError("test_Whois", 2);
	} catch (std::exception& e) {}
}

static void	test3()
{
	try
	{
		Whois			out("WHOIS hola 123");
		std::cerr << "Invalid number of arguments";
		printError("test_Whois", 3);
	} catch (std::exception& e) {}
}


void	test_Whois()
{
	test1();
	test2();
	test3();
}
