#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"

class server;

class Nick	 : public Command
{
private:
	size_t	_size;
	std::vector<std::string> _vec;
	char*	ERR_NONICKNAMEGIVEN(const std::string& serverIp) const;
	char*	ERR_ERRONEUSNICKNAME(const std::string& serverIp) const;
	char*	ERR_NICKNAMEINUSE(const std::string& serverIp) const;
public:
	Nick	(const std::vector<std::string>& vec);
	char*	execute(server& server, Client& client) const;
	bool	validNick() const;
	~Nick	();
};