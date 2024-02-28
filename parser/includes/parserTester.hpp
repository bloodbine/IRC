#pragma once

#include <cassert>
#include "parser.hpp"

#define RESET_COLOR "\033[0m"
#define BOLD_ON "\033[1m"
#define BOLD_OFF "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"

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

#define ASSERT_NOT_EQUAL(condition, message) \
	if (actual == expected) \
	{ \
		std::cerr << BOLD_ON << RED_COLOR; \
		std::cerr << "[ASSERT NOT EQUAL ERROR]: " << BOLD_OFF << RESET_COLOR  << message << std::endl; \
	} \


void	test_main();
void	test_split();

