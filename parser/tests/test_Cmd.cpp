#include "parserTester.hpp"

static void	testPrivmsg()
{
	std::vector<std::string>	in = split("PRIVMSG #channel :hello world");
	try
	{
		Cmd	*cmd = new Privmsg(in);
		Privmsg	*p = dynamic_cast<Privmsg*>((Privmsg*)cmd);
		assert(p);
	}
	catch(std::exception& e)
	{
		std::cout << e.what();
	}
}

static void	testPass()
{
	std::vector<std::string>	in = split("Pass helloWorld");
	try
	{
		Cmd	*cmd = new Pass(in);
		Pass	*p = dynamic_cast<Pass*>((Pass*)cmd);
		std::cout << std::boolalpha;
		std::cout << p->getPassword() << std::endl;
		std::cout << std::noboolalpha;
		assert(p);
	}
	catch(std::exception& e)
	{
		std::cout << e.what();
	}
}


void	test_Cmd()
{
	testPrivmsg();
	testPass();
}