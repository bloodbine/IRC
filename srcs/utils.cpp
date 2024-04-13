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

Command	*getCommand(Client* client, const std::vector<std::string>& vec)
{
	// if (vec[0] == "CAP") return (new Cap(client, vec));
	if (vec[0] == "PASS") return (new Pass(client, vec));
	// if (vec[0] == "NICK") return (new Nick(client, vec));
	// if (vec[0] == "USER") return (new User(client, vec));
	return NULL;
}

bool	isSpecialChar(char c)
{
	std::string special =  "[]\\`_^{|}";
	if (special.find(c) != std::string::npos) return true;
	return false;
}