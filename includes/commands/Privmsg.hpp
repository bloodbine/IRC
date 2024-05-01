#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Privmsg: public Command
{
private:
	/* data */
	Client* _client;
	size_t _size;
	std::string _msg;
	std::string _target;
	bool		_targetIsChannel;
public:
	Privmsg(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Privmsg();
};
