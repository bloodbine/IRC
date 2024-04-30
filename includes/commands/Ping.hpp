#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"
#include "Client.hpp"

class server;

class Ping	 : public Command
{
private:
	size_t		_size;
	std::string	_serverName;
	Client		*_client;
public:
	Ping	(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Ping	();
};
