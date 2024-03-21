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

void	test_Cmd()
{
	testPrivmsg();
}