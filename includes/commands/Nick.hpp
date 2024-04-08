#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>

class server;

class Nick	 : public Command
{
private:
	size_t	_size;
public:
	Nick	(const std::vector<std::string>& vec);
	char*	execute(server& Server) const;
	char*	ERR_NONICKNAMEGIVEN(const std::string& serverIp) const;
	~Nick	();
};