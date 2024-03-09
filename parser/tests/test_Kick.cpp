#include "parserTester.hpp"

static void	test_onlyCmd()
{
	try
	{
		std::vector<std::string>	in = split("KICK");
		Kick	cmd(in);
		printError("tests/test_Kick.cpp:9:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_cmdAndChannel()
{
	try
	{
		std::vector<std::string>	in = split("KICK #channel");
		Kick	cmd(in);
		printError("tests/test_Kick.cpp:19:0 => should throw an exception");
	} catch (std::exception& e)
	{
	}
}

static void	test_cmdAndUser()
{
	try
	{
		std::vector<std::string>	in = split("KICK channel");
		Kick	cmd(in);
		printError("tests/test_Kick.cpp:32:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_InvalidOrder()
{
	try
	{
		std::vector<std::string>	in = split("KICK user #channel");
		Kick	cmd(in);
		printError("tests/test_Kick.cpp:41:0 => should throw an exception");
	} catch (std::exception& e) {}
}

static void	test_cmdChannelAndUser()
{
	try
	{
		std::vector<std::string>	in = split("KICK #channel hola");
		Kick	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Kick.cpp:51:0 => Join has not correct channel");
		ASSERT_EQUAL(cmd.getUser(), "hola", "tests/test_Kick.cpp:52:0 => Join has not a correct User");
	} catch (std::exception& e)
	{
		printError("tests/test_Kick.cpp:46:0 => shouldn't throw an exception");
	}
}

static void	test_kickWithMessage()
{
	try
	{
		std::vector<std::string>	in = split("KICK #channel hola :hasta luego!");
		Kick	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Kick.cpp:42:0 => Join has not correct channel");
		ASSERT_EQUAL(cmd.getUser(), "hola", "tests/test_Kick.cpp:43:0 => Join has not a correct User");
		ASSERT_EQUAL(cmd.getMessage(), "hasta luego!", "tests/test_Kick.cpp:43:0 => Join has not a correct message");
	} catch (std::exception& e) {
		printError("tests/test_Kick.cpp:57:0 => shouldn't throw an exception");
	}
}

static void	test_kickWithMessage2()
{
	try
	{
		std::vector<std::string>	in = split("KICK #channel hola :hasta");
		Kick	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Kick.cpp:42:0 => Join has not correct channel");
		ASSERT_EQUAL(cmd.getUser(), "hola", "tests/test_Kick.cpp:43:0 => Join has not a correct User");
		ASSERT_EQUAL(cmd.getMessage(), "hasta", "tests/test_Kick.cpp:43:0 => Join has not a correct message");
	} catch (std::exception& e) {
		printError("tests/test_Kick.cpp:57:0 => shouldn't throw an exception");
	}
}

void	test_Kick()
{
	test_onlyCmd();
	test_cmdAndChannel();
	test_cmdAndUser();
	test_cmdChannelAndUser();
	test_InvalidOrder();
	test_kickWithMessage();
	test_kickWithMessage2();
}
