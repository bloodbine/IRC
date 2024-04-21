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
	size_t	_size;
	Client*	_client;
	std::string	_serverName;
	char *_out;
public:
	Ping	(Client* client, const std::vector<std::string>& vec);
	void execute();
	int sendToClient() const;
	~Ping	();
};
