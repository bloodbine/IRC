#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>

class server;

class Cap : public Command
{
private:
	std::string	_serverAddress;
	size_t	_size;
public:
	Cap(const std::vector<std::string>& vec);
	char*	execute(server& server, Client& client) const;
	~Cap();
};