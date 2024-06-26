#pragma once

#include "Command.hpp"
#include "Channel.hpp"
#include "server.hpp"

#include <sstream>

#define PASS 0
#define NICK 1
#define USER 2
#define PART 3
#define JOIN 4
#define PING 5
#define NOTICE 6
#define TOPIC 7
#define PRIVMSG 8
#define INVITE 9
#define KICK 10
#define QUIT 11
#define MODE 12
#define WHO 13
#define CAP 14

void						signal_handler(int signal);
std::string					getClientHostname(int clientFD);
std::string					getTimestamp();
void						addrStructToString(std::string &ip_dest, std::string &hostname_dest);
void						clearClientMessages(int clientFD);

// Command related
std::vector<std::string>	getVector(char *in);
int							getCmdType(const std::string& cmd);

// Validating
bool						isInvalidChannelName(const std::string& str);
bool						isSpecialChar(char c);
bool						isValidUser(const std::vector<std::string> userInfo);
bool						validNick(const std::string &nickname);
bool						isValidMode(const std::string& mode);
bool						stringIsNumeric(const char *string);

// Sending related
void						selfClientSend(const std::string stringToSend, int toSendFd, int flag);
void						sendToChannel(const std::string stringToSend, const std::string& channelName, const std::string& sender);


// Error handling
void						missingPass();
void						missingNick();
void	ERR_NEEDMOREPARAMS(const std::string& cmdName);
void	ERR_ALREADYREGISTRED();
void	ERR_NOTREGISTERED();
void	ERR_NOSUCHCHANNEL();
void	ERR_NOTONCHANNEL();
void	ERR_NOORIGIN();
void	ERR_NOSUCHSERVER(const std::string& server);
void	ERR_NOSUCHNICK(const std::string& nickName);
void	ERR_ERRONEUSNICKNAME(const std::string& nickName);
void	ERR_NICKNAMEINUSE(const std::string& nickName);
void	ERR_SYNTAXPROBLEM();
void	ERR_UMODEUNKNOWNFLAG();
void	ERR_CHANNELISFULL(const std::string& channelName);
void	ERR_INVITEONLYCHAN(const std::string& channelName);
void	ERR_BADCHANNELKEY(const std::string& channelName, const std::string& reason);
void	ERR_USERONCHANNEL(const std::string& channelName);
void	ERR_BADCHANMASK(const std::string& channelName);
void	ERR_CANTKICKYOURSELF();
void	ERR_USERNOTINCHANNEL(const std::string& channelName, const std::string& nickName);
void	ERR_CHANOPRIVSNEEDED(const std::string& channelName);
void	ERR_NOPRIVILEGES(const std::string& channelName);
void	ERR_TOOMANYCHANNELS(const std::string& channelName);
void	ERR_NONICKNAMEGIVEN();
void	ERR_INVALIDCOMMAND();
void	ERR_PASSWDMISMATCH();
void	ERR_CANNOTSENDTOCHAN(const std::string& channelName);
