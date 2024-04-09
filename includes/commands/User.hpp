#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "server.hpp"
#include "utils.hpp"

class server;

class User	 : public Command
{
private:
	size_t	_size;
	std::vector<std::string>	_vec;
	std::string					_userName;
public:
	User	(const std::vector<std::string>& vec);
	char*	execute(server& server, Client& client) const;
	bool	validUser() const;
	~User	();
};