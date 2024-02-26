#pragma once

#include <iostream>
#include <vector>
#include <string>

void	runTests();

// Compartions utils
template <typename T>
void	compareVectors(const std::vector<T>& out, const std::vector<T>& expected)
{
	if (out.size() != expected.size())
	{
		std::cout << "Vector size [out " << out.size() << "]" << " [expected " << expected.size() << "]" << std::endl;
	}
	else
	{
		typename std::vector<T>::const_iterator	i = out.begin();
		typename std::vector<T>::const_iterator	end = out.end();
		int							index = 0;
		for (; i < end; ++i)
		{
			if (out[index] != expected[index]) std::cout << "Vector out != expected" << std::endl;
			return ;
			index++;
		}
	}
}