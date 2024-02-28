#include "parser.hpp"

std::vector<std::string>	split(const std::string& text)
{
	std::vector<std::string>	out;
	std::stringstream			ss(text);
	std::string					word;

	while (ss >> word) out.push_back(word);
	return out;
}
