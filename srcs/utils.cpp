#include "utils.hpp"

std::vector<std::string> getVector(char *in)
{
	std::string					text(in);
	std::vector<std::string>	out;
	std::stringstream			ss(text);
	std::string					word;

	while (ss >> word) out.push_back(word);
	return out;
}

Command	*getCommand(const std::vector<std::string>& vec)
{
	if (vec[0] == "CAP") return (new Cap(vec));
	return NULL;
}