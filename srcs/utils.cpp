#include "utils.hpp"
#include "Channel.hpp"
#include <netdb.h>

std::string		getTimestamp()
{
	time_t t = time(0);
	struct tm* tinf = localtime(&t);
	char buffer[80];
	
	strftime(buffer, 80, "%H:%M:%S %b %d %Y", tinf);
	return std::string(buffer);
}

void addrStructToString(std::string &ip_dest, std::string &hostname_dest)
{
	char				host[256];
	struct hostent*		hostEntry;

	if (gethostname(host, sizeof(host)) == -1)
		throw std::logic_error("Failed to retrieve hostname");
	
	hostEntry = gethostbyname(host);
	if (!hostEntry)
	{
		ip_dest = "127.0.0.1";
		hostname_dest = "localhost";
	}
	else
	{
		ip_dest = inet_ntoa(*((struct in_addr*) hostEntry->h_addr_list[0]));
		std::cout << ">> Hostname: " << hostEntry->h_name << std::endl;
		hostname_dest = std::string(hostEntry->h_name);
	}
}

std::string getExecuteOut(Client *client, std::vector<std::string>& vec, bool *failedToSendMsg)
{
	std::string tmp;
	try
	{
		Command* cmd = getCommand(client, vec);
		if (cmd == NULL) tmp = "[ERROR]: UNSUPPORTED COMMAND\r\n";
		else
		{
			try
			{
				tmp = cmd->execute();
			}
			catch(const std::exception& e)
			{
				tmp = e.what();
			}
			delete cmd;
		}
	}
	catch (std::exception& e)
	{
		tmp = e.what();
		*failedToSendMsg = true;
	}
	return tmp;
}

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
	if (vec.size() < 1) return NULL;
	if (vec[0] == "CAP") return (new Cap(client, vec));
	if (vec[0] == "PASS") return (new Pass(client, vec));
	if (vec[0] == "NICK") return (new Nick(client, vec));
	if (vec[0] == "USER") return (new User(client, vec));
	if (vec[0] == "PART") return (new Part(client, vec));
	if (vec[0] == "JOIN") return (new Join(client, vec));
	if (vec[0] == "PING") return (new Ping(client, vec));
	if (vec[0] == "NOTICE") return (new Notice(client, vec));
	if (vec[0] == "TOPIC") return (new Topic(client, vec));
	if (vec[0] == "PRIVMSG") return (new Privmsg(client, vec));
	if (vec[0] == "INVITE") return (new Invite(client, vec));
	if (vec[0] == "KICK") return (new Kick(client, vec));
	if (vec[0] == "QUIT") return (new Quit(client, vec));
	if (vec[0] == "MODE") return (new Mode(client, vec));
	if (vec[0] == "SHUTDOWN") return (new Shutdown(client, vec));
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

bool	validNick(const std::string &nickname)
{
	if (nickname.size() > 1 && nickname.size() <= 9)
	{
		if (isSpecialChar(nickname[0]) || std::isalpha(nickname[0]))
		{
			std::string::const_iterator i = nickname.begin();
			i++;
			for (; i != nickname.end(); ++i)
			{
				if (isSpecialChar(*i) || std::isalnum(*i) || *i == '-')
					continue;
				return false;
			}
			return true;
		}
		return false;
	}
	return false;
}

void	missingPass()
{
	throw std::invalid_argument(" ERROR: YOU MUST PROVIDE A PASSWORD FIRST => PASS <password>\r\n");
}

void	missingNick()
{
	throw std::invalid_argument("You need to set NICK <nickname>!\r\n");
}

bool	isValidMode(const std::string& mode)
{
	std::string validModes = "itkol";
	if (mode.size() != 2 || (mode[0] != '+' && mode[0] != '-')) return false;
	if (validModes.find(mode[1]) != std::string::npos) return true;
	return false;
}

bool	stringIsNumeric(const char *string)
{
	for (size_t i = 0; i < strlen(string); ++i)
		if (isdigit(string[i]) == false) return false;
	return true;
}

void	ERR_NEEDMOREPARAMS(const std::string& cmdName)
{
	std::string	text = "461 " + cmdName +  " :Not enough parameters\r\n";
	throw std::invalid_argument(text);
}

void	ERR_ALREADYREGISTRED()
{
	throw std::invalid_argument(" 462 :Unauthorized command (already registered)\r\n");
}
void	ERR_NOTREGISTERED()
{
	throw std::invalid_argument(" 451 :You have not registered\r\n");
}

void	ERR_NOSUCHCHANNEL()
{
	throw std::invalid_argument(" 403 :No such channel\r\n");
}
void	ERR_NOTONCHANNEL()
{
	throw std::invalid_argument(" 442 :You're not on that channel\r\n");
}

void	ERR_NOORIGIN()
{
	throw  std::invalid_argument(" 409 :No origin specified\r\n");
}

void	ERR_NOSUCHSERVER(const std::string& server)
{
	throw  std::invalid_argument(server + " 402 :No such server\r\n");
}

void	ERR_NOSUCHNICK(const std::string& nickName)
{
	throw  std::invalid_argument(nickName + " 401 :No such nick/channel\r\n");
}

void	ERR_ERRONEUSNICKNAME(const std::string& nickName)
{
	throw  std::invalid_argument(nickName + " 432 :Erroneous nickname\r\n");
}

void	ERR_NICKNAMEINUSE(const std::string& nickName)
{
	throw  std::invalid_argument(nickName + " 433 :Nickname is already in use\r\n");
}

void	ERR_SYNTAXPROBLEM()
{
	throw  std::invalid_argument(":127.0.0.1 430 : invalid syntax my friend\r\n");
}

void	ERR_UMODEUNKNOWNFLAG()
{
	throw  std::invalid_argument(" 501 :Unknown MODE flag\r\n");
}
// Greg
void	ERR_NOPRIVILEGES(const std::string& channelName)
{
	throw std::invalid_argument(" 481 " + channelName + " :Permission Denied- You're not an IRC operator\r\n");
}

void	ERR_CHANNELISFULL(const std::string& channelName)
{
	throw std::invalid_argument(" 471 " + channelName + " :Channel is full\r\n");
}
void	ERR_INVITEONLYCHAN(const std::string& channelName)
{
	throw std::invalid_argument(" 473 " + channelName + " :Channel is invite-only\r\n");
}
void	ERR_BADCHANNELKEY(const std::string& channelName, const std::string& reason)
{
	throw std::invalid_argument(" 475 " + channelName + " :" + reason + "\r\n");
}

void ERR_USERONCHANNEL(const std::string& channelName)
{
	throw std::invalid_argument(" " + channelName + " :User already on channel\r\n");
}

// void ERR_USERNOTINCHANNEL(const std::string& channelName,const std::string& nickName)
// {
// 	throw std::invalid_argument(nickName + " " + channelName + " :They aren't on that channel");
// }

void ERR_BADCHANMASK(const std::string& channelName)
{
	throw std::invalid_argument(channelName + " :Bad Channel Mask\r\n");
}

void ERR_CANTKICKYOURSELF()
{
	throw std::invalid_argument("Dear friend, you can't kick yourself. Use PART instead\r\n");
}
void ERR_USERNOTINCHANNEL(const std::string& channelName, const std::string& nickName)
{
	throw std::invalid_argument("441 " + nickName + channelName + "  :They aren't on that channel\r\n");
}
void ERR_CHANOPRIVSNEEDED(const std::string& channelName)
{
	throw std::invalid_argument("482 " + channelName + " :You're not channel operator\r\n");
}

void ERR_TOOMANYCHANNELS(const std::string& channelName)
{
	throw std::invalid_argument("405 " + channelName + " :You have joined too many channels\r\n");
}