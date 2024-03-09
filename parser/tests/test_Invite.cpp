#include "parserTester.hpp"

static void	test_onlyCmd()
{
	try
	{
		std::vector<std::string>	in = split("INVITE");
		Invite	cmd(in);
		printError("tests/test_Invite.cpp:9:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_cmdAndChannel()
{
	try
	{
		std::vector<std::string>	in = split("INVITE #channel");
		Invite	cmd(in);
		printError("tests/test_Invite.cpp:19:0 => should throw an exception");
	} catch (std::exception& e)
	{
	}
}

static void	test_cmdAndUser()
{
	try
	{
		std::vector<std::string>	in = split("INVITE channel");
		Invite	cmd(in);
		printError("tests/test_Invite.cpp:32:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_InvalidOrder()
{
	try
	{
		std::vector<std::string>	in = split("INVITE user #channel");
		Invite	cmd(in);
		printError("tests/test_Invite.cpp:41:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_cmdChannelAndUser()
{
	try
	{
		std::vector<std::string>	in = split("INVITE #channel hola");
		Invite	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Invite.cpp:51:0 => Join has not correct channel");
		ASSERT_EQUAL(cmd.getUser(), "hola", "tests/test_Invite.cpp:52:0 => Join has not a correct User");
	} catch (std::exception& e)
	{
		printError("tests/test_Invite.cpp:46:0 => shouldn't throw an exception");
	}
}

void	test_Invite()
{
	test_onlyCmd();
	test_cmdAndChannel();
	test_cmdAndUser();
	test_cmdChannelAndUser();
	test_InvalidOrder();
}
