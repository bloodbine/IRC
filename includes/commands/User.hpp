#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"
#include "Client.hpp"

class server;

class User	 : public Command
{
private:
	size_t	_size;
	std::vector<std::string>	_vec;
	std::string					_userName;
	Client						*_client;
	char *_out;
public:
	User	(Client* client, const std::vector<std::string>& vec);
	void execute();
	bool	validUser() const;
	int 	sendToClient() const;
	~User	();
};