#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "Client.hpp"

class server;

class Cap : public Command
{
private:
	size_t	_size;
	Client	*_client;
	std::string _serverAddress;
public:
	Cap(Client* client, const std::vector<std::string>& vec);
	char* execute() const;
	~Cap();
};