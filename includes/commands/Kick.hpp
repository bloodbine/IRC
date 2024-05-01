#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Kick: public Command
{
private:
	/* data */
	Client* _client;
	size_t _size;
	std::string _channel;
	std::string _nick;
	std::string _reason;
public:
	Kick(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Kick();
};
