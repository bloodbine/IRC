#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

std::vector<std::string>	split(const std::string& text);

// Utils
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