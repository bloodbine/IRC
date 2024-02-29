#pragma once

#include <cassert>
#include "parser.hpp"

#define ASSERT(condition, message) \
	if (!condition) \
	{ \
		std::cerr << BOLD_ON << RED_COLOR; \
		std::cerr << "[ASSERT ERROR]: " << BOLD_OFF << RESET_COLOR  << message << std::endl; \
	} \

#define ASSERT_EQUAL(actual, expected, message) \
	if (actual != expected) \
	{ \
		std::cerr << BOLD_ON << RED_COLOR; \
		std::cerr << "[ASSERT EQUAL ERROR]: " << BOLD_OFF << RESET_COLOR  << message << std::endl; \
	} \

#define ASSERT_NOT_EQUAL(actual, expected, message) \
	if (actual == expected) \
	{ \
		std::cerr << BOLD_ON << RED_COLOR; \
		std::cerr << "[ASSERT NOT EQUAL ERROR]: " << BOLD_OFF << RESET_COLOR  << message << std::endl; \
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
