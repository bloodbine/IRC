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
	if (vec[0] == "CAP") return (new Cap(client, vec));
	if (vec[0] == "PASS") return (new Pass(client, vec));
	if (vec[0] == "NICK") return (new Nick(client, vec));
	if (vec[0] == "USER") return (new User(client, vec));
	return NULL;
}

bool	isSpecialChar(char c)
{
	std::string special =  "[]\\`_^{|}";
	if (special.find(c) != std::string::npos) return true;
	return false;
}

void	missingPass()
{
	throw std::invalid_argument(" ERROR: YOU MUST PROVIDE A PASSWORD FIRST => PASS <password>\n");
}

void	missingNick()
{
	throw std::invalid_argument("You need to set NICK <nickname>!\n");
}

void	ERR_NEEDMOREPARAMS(const std::string& cmdName)
{
	std::string	text = "461 " + cmdName +  " :Not enough parameters\n";
	throw std::invalid_argument(text);
}


void	ERR_ALREADYREGISTRED()
{
	throw std::invalid_argument(" 462 :Unauthorized command (already registered)\n");
}