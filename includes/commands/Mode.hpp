#pragma once 

#include <iostream>
#include "Command.hpp"
#include "Channel.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Mode: public Command
{
private:
	/* data */
	Client*		_client;
	Channel*	_channelObj;
	size_t		_size;
	std::string	_channel;
	std::string	_mode;
	std::string	_parameter;
public:
	Mode(Client* client, const std::vector<std::string>& vec);
	std::string execute() const;
	~Mode();
};
