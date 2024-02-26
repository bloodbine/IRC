#include "parserTest.hpp"

typedef struct s_test_privmsg
{
	bool		targetIsUser;
	std::string	target;
	std::string	message;
} t_test_privmsg;


static void	compare(int caseNum, Privmsg& out, t_test_privmsg expect)
{
	bool		targetIsUser = out.getTargetIsUser();
	std::string	target = out.getTarget();
	std::string	message = out.getMessage();

	if (targetIsUser != expect.targetIsUser)
	{
		std::cout << "targetIsUser [out " << targetIsUser << "] [expect " << expect.targetIsUser << "]";
		printError("test_Privmsg", caseNum);
	}
	if (target != expect.target)
	{
		std::cout << "target [out " << target << "] [expect " << expect.target << "]";
		printError("test_Privmsg", caseNum);
	}
	if (message != expect.message)
	{
		std::cout << "message [out " << message << "] [expect " << expect.message << "]";
		printError("test_Privmsg", caseNum);
	}
}

static void	test1()
{
	Privmsg			out("PRIVMSG #channel :Hola");
	t_test_privmsg	expect;

	expect.targetIsUser = false;
	expect.target = "channel";
	expect.message = "Hola";
	compare(1, out, expect);
}


static void	test2()
{
	try
	{
		Privmsg			out("PRIVMSG #channel #channel2 :Hola");
		std::cout << "you must throw error when multiple channels are specified";
		printError("test_Privmsg", 2);
	}
	catch (std::exception& e) {}
}

static void	test3()
{
	try
	{
		Privmsg			out("PRIVMSG user user2 :Hola");
		std::cout << "you must throw error when multiple users are specified";
		printError("test_Privmsg", 2);
	}
	catch (std::exception& e) {}
}

static void	test4()
{
	Privmsg			out("PRIVMSG user :Hola");
	t_test_privmsg	expect;

	expect.targetIsUser = true;
	expect.target = "user";
	expect.message = "Hola";
	compare(1, out, expect);
}

void	test_Privmsg()
{
	test1();
	test2();
	test3();
	test4();
}
