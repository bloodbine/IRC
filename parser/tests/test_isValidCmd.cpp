#include "parserTester.hpp"

static void	testEmptyString()
{
	std::string		in = "";

	ASSERT_EQUAL(isValidCmd(in), -1, "testEmptyString()");
}

static void	testError()
{
	std::string		in = "random";
	std::string		in2 = "random something else";

	ASSERT_EQUAL(isValidCmd(in), -1, "testError()");
	ASSERT_EQUAL(isValidCmd(in), -1, "testError('random something else')");
}

static void	testPrivMsg()
{
	std::string		in = "PRIVMSG";
	std::string		in2 = "PRIVMSG hola mundo";

	ASSERT_EQUAL(isValidCmd(in), PRIVMSG, "testPrivMsg('PRIVMSG')");
	ASSERT_EQUAL(isValidCmd(in), PRIVMSG, "testPrivMsg('PRIVMSG hola mundo')");
}

static void	testPass()
{
	std::string		in = "PASS";
	std::string		in2 = "PASS 123 5421 hi";

	ASSERT_EQUAL(isValidCmd(in), PASS, "testPass('PASS')");
	ASSERT_EQUAL(isValidCmd(in), PASS, "testPass('PASS 123 5421 hi')");
}

static void	testWhois()
{
	std::string		in = "WHOIS";

	ASSERT_EQUAL(isValidCmd(in), WHOIS, "testWhois('WHOIS')");
}

static void	testWho()
{
	std::string		in = "WHO";

	ASSERT_EQUAL(isValidCmd(in), WHO, "testWho('WHO')");
}

static void	testPing()
{
	std::string		in = "PING";

	ASSERT_EQUAL(isValidCmd(in), PING, "testPing('PING')");
}

static void	testCap()
{
	std::string		in = "CAP";

	ASSERT_EQUAL(isValidCmd(in), CAP, "testCap('CAP')");
}

static void	testPart()
{
	std::string		in = "PART";

	ASSERT_EQUAL(isValidCmd(in), PART, "testPart('PART')");
}

static void	testList()
{
	std::string		in = "LIST";

	ASSERT_EQUAL(isValidCmd(in), LIST, "testList('LIST')");
}

static void	testMode()
{
	std::string		in = "MODE";

	ASSERT_EQUAL(isValidCmd(in), MODE, "testMode('MODE')");
}

static void	testQuit()
{
	std::string		in = "QUIT";

	ASSERT_EQUAL(isValidCmd(in), QUIT, "testQuit('QUIT')");
}

static void	testTopic()
{
	std::string		in = "TOPIC";

	ASSERT_EQUAL(isValidCmd(in), TOPIC, "testTopic('TOPIC')");
}

static void	testJoin()
{
	std::string		in = "JOIN";

	ASSERT_EQUAL(isValidCmd(in), JOIN, "testJoin('JOIN')");
}

static void	testNick()
{
	std::string		in = "NICK";

	ASSERT_EQUAL(isValidCmd(in), NICK, "testNick('NICK')");
}

static void	testMotd()
{
	std::string		in = "MOTD";

	ASSERT_EQUAL(isValidCmd(in), MOTD, "testMotd('MOTD')");
}

void	test_isValidCmd()
{
	testEmptyString();
	testPrivMsg();
	testError();
	testPass();
	testWhois();
	testWho();
	testPing();
	testCap();
	testPart();
	testList();
	testMode();
	testQuit();
	testTopic();
	testJoin();
	testNick();
	testMotd();
}
