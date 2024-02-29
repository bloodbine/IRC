#include "parserTester.hpp"

void	test_main()
{
	test_split();
	test_isValidCmd();
	test_Privmsg();
	test_isValidUser();
	test_isValidChannel();
	test_Pass();
	test_Nick();
	test_Whois();
	test_Who();
}