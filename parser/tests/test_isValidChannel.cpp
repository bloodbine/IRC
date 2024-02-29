#include "parserTester.hpp"

static void	testWrongBecauseIsUser()
{
	ASSERT_EQUAL(isValidChannelName("school"), false, "testWrongBecauseIsChannel() should be false")
}

static void	testChannelTooLong()
{
	bool	out = isValidUserName("#holamundoestoesunusuariomuylargoholamundoestoesunusuariomuylargo");
	ASSERT_EQUAL(out, false, "testChannelTooLong() should be false")
}

static void	testChannelTooShort()
{
	bool	out = isValidUserName("#ab");
	ASSERT_EQUAL(out, false, "testChannelTooShort() should be false")
}

static void	testValidChannel()
{
	bool	out = isValidChannelName("#abcdeff");
	ASSERT_EQUAL(out, true, "tests/isValidChannel.cpp:23:0 => should be true")
}

static void	testChannelStartWithDigit()
{
	bool	out = isValidChannelName("#1hola");
	ASSERT_EQUAL(out, false, "testChannelStartWithDigit() should be false")
}

static void	testChannelContainsDigitButNotAtStart()
{
	bool	out = isValidChannelName("#hol4");
	ASSERT_EQUAL(out, true, "testChannelContainsDigitButNotAtStart() should be true")
}

static void	testNormalChannel()
{
	bool	out = isValidChannelName("#hola");
	ASSERT_EQUAL(out, true, "testNormalChannel() should be true")
}

static void	testWrongChannel()
{
	bool	out = isValidChannelName(":hola");
	ASSERT_EQUAL(out, false, "testWrongChannel() should be false")
}

void	test_isValidChannel()
{
	testWrongBecauseIsUser();
	testChannelTooLong();
	testChannelStartWithDigit();
	testChannelContainsDigitButNotAtStart();
	testNormalChannel();
	testWrongChannel();
	testChannelTooShort();
	testValidChannel();
}