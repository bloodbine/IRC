#include "parserTester.hpp"

void	test_onlyCmd()
{
	try
	{
		std::vector<std::string>	in = split("JOIN");
		Join	cmd(in);
		printError("tests/test_Join.cpp:8:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_cmdAndChannel()
{
	try
	{
		std::vector<std::string>	in = split("JOIN #channel");
		Join	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Join.cpp:19:0 => Join has not a channel called 'channel'");
	} catch (std::exception& e)
	{
		printError("tests/test_Join.cpp:22:0 => should't throw an exception");
	}
}

void	test_cmdAndNotValidChannel()
{
	try
	{
		std::vector<std::string>	in = split("JOIN channel");
		Join	cmd(in);
		printError("tests/test_Join.cpp:32:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_cmdChannelAndPassword()
{
	try
	{
		std::vector<std::string>	in = split("JOIN #channel hola");
		Join	cmd(in);
		ASSERT_EQUAL(cmd.getChannel(), "channel", "tests/test_Join.cpp:42:0 => Join has not a channel called 'channel'");
		ASSERT_EQUAL(cmd.getPassword(), "hola", "tests/test_Join.cpp:43:0 => Join has not a correct password");
	} catch (std::exception& e)
	{
		printError("tests/test_Join.cpp:46:0 => shouldn't throw an exception");
	}
}

void	test_invalidArgs()
{
	try
	{
		std::vector<std::string>	in = split("JOIN #channel hola mundo");
		Join	cmd(in);
		printError("tests/test_Join.cpp:57:0 => should throw an exception");
	} catch (std::exception& e) {}
}

void	test_invalidPassword()
{
	try
	{
		std::vector<std::string>	in = split("JOIN #channel thisisaverylongpasswordthisisaverylongpasswordthisisaverylongpassword");
		Join	cmd(in);
		printError("tests/test_Join.cpp:68:0 => should throw an exception");

	} catch (std::exception& e) {}
}

void	test_Join()
{
	test_onlyCmd();
	test_cmdAndChannel();
	test_cmdAndNotValidChannel();
	test_cmdChannelAndPassword();
	test_invalidArgs(); 
}