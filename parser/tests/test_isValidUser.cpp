#include "parserTester.hpp"

static void	testWrongBecauseIsChannel()
{
	ASSERT_EQUAL(isValidUserName("#school"), false, "testWrongBecauseIsChannel() should be false")
}

static void	testUserTooLong()
{
	bool	out = isValidUserName("holamundoestoesunusuariomuylargoholamundoestoesunusuariomuylargo");
	ASSERT_EQUAL(out, false, "testUserTooLong() should be false")
}

static void	testUserStartWithDigit()
{
	bool	out = isValidUserName("1hola");
	ASSERT_EQUAL(out, false, "testUserStartWithDigit() should be false")
}

static void	testUserContainsDigitButNotAtStart()
{
	bool	out = isValidUserName("hol4");
	ASSERT_EQUAL(out, true, "testUserContainsDigitButNotAtStart() should be true")
}

static void	testNormalUser()
{
	bool	out = isValidUserName("hola");
	ASSERT_EQUAL(out, true, "testNormalUser() should be true")
}

void	test_isValidUser()
{
	testWrongBecauseIsChannel();
	testUserTooLong();
	testUserStartWithDigit();
	testUserContainsDigitButNotAtStart();
	testNormalUser();
}