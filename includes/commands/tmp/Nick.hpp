#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"
#include "Client.hpp"

class server;

class Nick: public Command
{
private:
	Client	*_client;
	std::string	_nickName;
	size_t	_size;
public:
	Nick	(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Nick	();
};