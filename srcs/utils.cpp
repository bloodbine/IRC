#include "utils.hpp"
#include "Channel.hpp"
#include <netdb.h>

std::string getClientHostname(int clientFD)
{
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
		
	if (getpeername(clientFD, (struct sockaddr*)&clientAddr, &clientAddrLen) == -1) {
		std::cerr << "Error getting client address" << std::endl;
		return ("Error");
	}

	char hostBuffer[NI_MAXHOST];
	char serviceBuffer[NI_MAXSERV];
	if (getnameinfo((struct sockaddr*)&clientAddr, sizeof(clientAddr), hostBuffer, sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), 0) != 0) {
		std::cerr << "Error getting client info" << std::endl;
		return ("Error");
	}

	return std::string(hostBuffer);
}

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

// std::string getExecuteOut(Client *client, std::vector<std::string>& vec, bool *failedToSendMsg)
// {
// 	std::string tmp;
// 	try
// 	{
// 		Command* cmd = getCommand(client, vec);
// 		if (cmd == NULL) tmp = "[ERROR]: UNSUPPORTED COMMAND\r\n";
// 		else
// 		{
// 			try
// 			{
// 				tmp = cmd->execute();
// 			}
// 			catch(const std::exception& e)
// 			{
// 				tmp = e.what();
// 				*failedToSendMsg = true;
// 			}
// 			delete cmd;
// 		}
// 	}
// 	catch (std::exception& e)
// 	{
// 		tmp = e.what();
// 		*failedToSendMsg = true;
// 	}
// 	return tmp;
// }

std::vector<std::string> getVector(char *in)
{
	std::string					text(in);
	std::vector<std::string>	out;
	std::stringstream			ss(text);
	std::string					word;

	while (ss >> word) out.push_back(word);
	return out;
}

/*
Returns the code with the type of command of command.
If it is not a valid command returns -1.
*/
int	getCmdType(const std::string& cmd)
{
	if (cmd == "PASS")		return PASS;
	if (cmd == "NICK")		return NICK;
	if (cmd == "USER")		return USER;
	if (cmd == "PART")		return PART;
	if (cmd == "JOIN")		return JOIN;
	if (cmd == "PING")		return PING;
	if (cmd == "NOTICE")	return NOTICE;
	if (cmd == "TOPIC")		return TOPIC;
	if (cmd == "PRIVMSG")	return PRIVMSG;
	if (cmd == "INVITE")	return INVITE;
	if (cmd == "KICK")		return KICK;
	if (cmd == "QUIT")		return QUIT;
	if (cmd == "MODE")		return MODE;	
	if (cmd == "SHUTDOWN")	return SHUTDOWN;
	return -1;
}

void	signal_handler(int signal)
{
	(void)signal;
	// implement channelList and clientList getters 
	std::map<std::string, Channel*>					channelList = server::getChannelList();
	std::map<std::string, Channel*>::iterator		itr1 = channelList.begin();
	std::map<std::string, Channel*>::iterator		end1 = channelList.end();
	for (; itr1 != end1; ++itr1) delete (*itr1).second;

	std::map<int, Client*>					clientList = server::getClientList();
	std::map<int, Client*>::iterator		itr2 = clientList.begin();
	std::map<int, Client*>::iterator		end2 = clientList.end();
	for (; itr2 != end2; ++itr2) delete (*itr2).second;

	server::getMessageList().clear();

	std::cout << "Signal was called!" << std::endl;
	server::setFinished(true);
}

bool	isInvalidChannelName(const std::string& str)
{
	if (str.size() == 1) return true;
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

bool	validUsernameFormat(const std::string& username)
{
	if (username.size() < 2) return false;
	if (username.size() > 1 && username.size() <= 9)
	{
		std::string	invalid = "\x00\x0A\x0D\x20\x40";
		std::string::const_iterator end = username.end();
		for (std::string::const_iterator itr = username.begin(); itr != end; ++itr)
		{
			if (invalid.find(*itr) != std::string::npos) return false;
			if (!isalpha(*itr)) return false;
		}
	}
	return true;
}

bool	validRealUsernameFormat(const std::string& username)
{
	if (username.size() < 3) return false;
	std::string::const_iterator end = username.end();
	int i = 0;
	for (std::string::const_iterator itr = username.begin(); itr != end; ++itr)
	{
		std::string	invalid = "\x00\x0A\x0D\x20\x40";
		if (i == 0 && *itr == ':')
		{
			i++;
			continue ;
		}
		if (invalid.find(*itr) != std::string::npos) return false;
		if (!isalpha(*itr)) return false;
		i++;
	}
	return true;
}


bool	isValidUser(const std::vector<std::string> userInfo)
{
	size_t	size = userInfo.size();
	if (size < 5 || size > 7) return false;
	/* check if valid username format */
	if (!validUsernameFormat(userInfo[1])) return false;
	if (userInfo[2] != "0") return false;
	if (userInfo[3] != "*") return false;
	/* check valid real username format */
	if (!validRealUsernameFormat(userInfo[4])) return false;
	return true;
}

void	missingPass()
{
	throw std::invalid_argument(" 462 :YOU MUST PROVIDE A PASSWORD FIRST => PASS <password>\r\n");
}

void	missingNick()
{
	throw std::invalid_argument(" 462 :You need to set NICK <nickname>!\r\n");
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
	throw  std::invalid_argument(":" + server::getHostname() + " 430 : invalid syntax my friend\r\n");
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
	throw std::invalid_argument(" 443 " + channelName + " :User already on channel\r\n");
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
	throw std::invalid_argument(" 462 :Dear friend, you can't kick yourself. Use PART instead\r\n");
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

void	ERR_INVALIDCOMMAND()
{
	throw std::invalid_argument(" 462 :Invalid command\r\n");
}

void	ERR_PASSWDMISMATCH()
{
	throw std::invalid_argument(" 462 :Password incorrect\n");
}

void	ERR_NONICKNAMEGIVEN()
{
	throw std::invalid_argument(" 431 :No nickname given\r\n");
}

void	ERR_CANNOTSENDTOCHAN(const std::string& channelName)
{
	throw std::invalid_argument("405 " + channelName + " :Cannot send to channel\r\n");
}

/*
Normally used to send error message or feedback to the client that
made the request.
*/
void	selfClientSend(const std::string& stringToSend, int toSendFd)
{
	server::messageList.insert(std::pair<int, std::string>(toSendFd, stringToSend));
}

/*
On failure returns -1.
On success returns 1
*/
void	sendToChannel(const std::string& stringToSend, const std::string& channelName)
{
	if (server::channelExists(channelName) == true)
	{
		Channel *channel = server::getChannelByName(channelName);
		std::map<std::string, Client*>	memberList = channel->getMemberList();
		std::map<std::string, Client*>::iterator itr = memberList.begin();
		std::map<std::string, Client*>::iterator end = memberList.end();
		for (; itr != end; ++itr)
		{
			Client*	tmpClient = (*itr).second;
			int	toSendFd = tmpClient->getFd();
			server::messageList.insert(std::pair<int, std::string>(toSendFd, stringToSend));
		}
	}
}
