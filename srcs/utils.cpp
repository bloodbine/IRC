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
	if (vec[0] == "PASS") return (new Pass(vec));
	if (vec[0] == "NICK") return (new Nick(vec));
	return NULL;
}

bool	isSpecialChar(char c)
{
	std::string special =  "[]\\`_^{|}";
	if (special.find(c) != std::string::npos) return true;
	return false;
}