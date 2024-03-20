#pragma once

#include <cassert>
#include "parser.hpp"

#define ASSERT_EQUAL(actual, expected, message) \
	if (actual != expected) \
	{ \
		std::cerr << BOLD_ON << RED_COLOR; \
		std::cerr << "[ASSERT EQUAL ERROR]: " << BOLD_OFF << RESET_COLOR  << message << std::endl; \
	} \

void	test_main();
void	test_split();
void	test_isValidUser();
void	test_isValidChannel();
void	test_isValidCmd();

/*
Testing commands
*/
void	test_Privmsg();
void	test_Pass();
void	test_Nick();
void	test_Whois();
void	test_Who();
void	test_Ping();
void	test_Part();
void	test_List();
void	test_Join();
void	test_Quit();
void	test_Topic();
void	test_Motd();
void	test_Kick();
void	test_Invite();
void	test_Mode();
