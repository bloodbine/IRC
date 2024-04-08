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
public:
	Nick	(const std::vector<std::string>& vec);
	char*	execute(server& Server) const;
	bool	validNick() const;
	char*	ERR_NONICKNAMEGIVEN(const std::string& serverIp) const;
	char*	ERR_ERRONEUSNICKNAME(const std::string& serverIp) const;
	~Nick	();
};