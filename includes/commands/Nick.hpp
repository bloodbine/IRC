#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"
#include "Client.hpp"

class server;

class Nick	 : public Command
{
private:
	Client	*_client;
	std::string	_nickName;
	size_t	_size;
	// char*	ERR_NONICKNAMEGIVEN(const std::string& serverIp) const;
	// char*	ERR_ERRONEUSNICKNAME(const std::string& serverIp) const;
	// char*	ERR_NICKNAMEINUSE(const std::string& serverIp) const;
public:
	Nick	(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Nick	();
};