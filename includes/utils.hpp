#pragma once

#include "Command.hpp"
#include "commands/Cap.hpp"
#include "commands/Pass.hpp"
#include "commands/Nick.hpp"
#include "commands/User.hpp"
#include "commands/Part.hpp"
#include "Channel.hpp"
#include <sstream>

std::vector<std::string> getVector(char *in);
Command	*getCommand(Client* client, const std::vector<std::string>& vec);
bool	isSpecialChar(char c);
void	missingPass();
void	missingNick();

/*
Error handling
*/
void	ERR_NEEDMOREPARAMS(const std::string& cmdName);
void	ERR_ALREADYREGISTRED();
void    ERR_NOTREGISTERED();
void	ERR_NOSUCHCHANNEL();
void	ERR_NOTONCHANNEL();
