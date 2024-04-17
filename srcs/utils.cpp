#include "utils.hpp"
#include "Channel.hpp"

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
	if (vec[0] == "PART") return (new Part(client, vec));
	if (vec[0] == "JOIN") return (new Join(client, vec));
	if (vec[0] == "PING") return (new Ping(client, vec));
	return NULL;
}

bool	isInvalidChannelName(const std::string& str)
{
	std::string::const_iterator	itr = str.begin();
	std::string::const_iterator	end = str.end();
	int							i = 0;
	for (; itr != end; ++itr)
	{
		if (i == 0 && str[0] != '#') return true;
		else if (*itr == '\a' || *itr == ' ' || *itr == ',' || *itr == ':') return true;
	}
	return false;
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
void	ERR_NOTREGISTERED()
{
	throw std::invalid_argument(" 451 :You have not registered\n");
}

void	ERR_NOSUCHCHANNEL()
{
	throw std::invalid_argument(" 403 :No such channel\n");
}
void	ERR_NOTONCHANNEL()
{
	throw std::invalid_argument(" 442 :You're not on that channel\n");
}

void	ERR_NOORIGIN()
{
	throw  std::invalid_argument(" 409 :No origin specified\n");
}

void	ERR_NOSUCHSERVER(const std::string& server)
{
	throw  std::invalid_argument(server + " 402 :No such server\n");
}
