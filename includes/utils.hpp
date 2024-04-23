#pragma once

#include "Command.hpp"
#include "Channel.hpp"
#include "commands/Cap.hpp"
#include "commands/Pass.hpp"
#include "commands/Nick.hpp"
#include "commands/User.hpp"
#include "commands/Part.hpp"
#include "commands/Join.hpp"
#include "commands/Ping.hpp"
#include "commands/Notice.hpp"
#include "commands/Topic.hpp"
#include "commands/Privmsg.hpp"
#include "commands/Invite.hpp"
#include "commands/Kick.hpp"
#include "commands/Quit.hpp"
#include "commands/Mode.hpp"
#include <sstream>

std::vector<std::string> getVector(char *in);
Command	*getCommand(Client* client, const std::vector<std::string>& vec);
bool	isInvalidChannelName(const std::string& str);
bool	isSpecialChar(char c);
bool	validNick(const std::string &nickname);
void	missingPass();
void	missingNick();
bool	isValidMode(const std::string& mode);

/*
Error handling
*/
void	ERR_NEEDMOREPARAMS(const std::string& cmdName);
void	ERR_ALREADYREGISTRED();
void    ERR_NOTREGISTERED();
void	ERR_NOSUCHCHANNEL();
void	ERR_NOTONCHANNEL();
void	ERR_NOORIGIN();
void	ERR_NOSUCHSERVER(const std::string& server);
void	ERR_NOSUCHNICK(const std::string& nickName);
void	ERR_ERRONEUSNICKNAME(const std::string& nickName);
void	ERR_NICKNAMEINUSE(const std::string& nickName);
void	ERR_SYNTAXPROBLEM();