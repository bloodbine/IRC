#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Privmsg.hpp"
#include "Pass.hpp"

// Utils
bool	isValidUserName(const std::string& name);
std::vector<std::string>	split(const std::string& text);

// Validation
bool	isValidPrivmsg(const std::string& text);

// Debugging
template <typename T>
void	printVector(const T& vec)
{
	typename T::const_iterator	i = vec.begin();
	typename T::const_iterator	e = vec.end();

	if (vec.size() != 0)
	{
		for (; i != e; ++i) std::cout << ", " << *i;
	}
	std::cout << std::endl;
}