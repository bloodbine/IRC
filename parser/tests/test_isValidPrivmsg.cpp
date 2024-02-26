#include "parserTest.hpp"

static void	test1()
{
	bool	out = isValidPrivmsg("PRIVMSG #channel1 :hola");
	bool	expect = true;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG #channel1 :hola'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 1);
	}
}

static void	test2()
{
	bool	out = isValidPrivmsg("PRIVMSG user :hola");
	bool	expect = true;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG user :hola'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 2);
	}
}

static void	test3()
{
	bool	out = isValidPrivmsg("PRIVMSG :hola");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG :hola'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 3);
	}
}

static void	test4()
{
	bool	out = isValidPrivmsg("PRIVMSG #channel1 :");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG #channel1 :'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 4);
	}
}

static void	test5()
{
	bool	out = isValidPrivmsg("PRIVMSG #channel1 #channel2 :world");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG #channel1 #channel2 :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 5);
	}
}

static void	test6()
{
	bool	out = isValidPrivmsg("PRIVMSG user1 user2 :world");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG user1 user2 :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 6);
	}
}

static void	test7()
{
	bool	out = isValidPrivmsg("PRIVMSG 123user :world");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG 123user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 7);
	}
}

static void	test8()
{
	bool	out = isValidPrivmsg("PRIVMSG #123user :world");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG #123user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 8);
	}
}

static void	test9()
{
	bool	out = isValidPrivmsg("PRIVMSG _user :world");
	bool	expect = true;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG _user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 9);
	}
}

static void	test10()
{
	bool	out = isValidPrivmsg("PRIVMSG #_user :world");
	bool	expect = true;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG #_user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 10);
	}
}

static void	test11()
{
	bool	out = isValidPrivmsg("PRIVMSG &_user :world");
	bool	expect = true;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG &_user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 11);
	}
}

static void	test12()
{
	bool	out = isValidPrivmsg("PRIVMSG !_user :world");
	bool	expect = false;
	if (compare(out, expect) == false)
	{
		std::cout << ANSI_BOLD << ANSI_YELLOW << "input: " << ANSI_GREEN << "'PRIVMSG !_user :world'" << ANSI_RESET;
		printError("test_isValidPrivmsg", 12);
	}
}

void	test_isValidPrivmsg() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
}
