#pragma once

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class Notice: public Command
{
private:
	/* data */
	Client* _client;
	size_t _size;
public:
	Notice(Client* client, const std::vector<std:: string>& vec);
	std::string execute() const;
	~Notice();
};