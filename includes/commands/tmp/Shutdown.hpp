#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"
#include "Client.hpp"

class server;

class Shutdown: public Command
{
private:
	Client	*_client;
	std::string	_password;
	size_t	_size;
public:
	Shutdown	(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Shutdown	();
};