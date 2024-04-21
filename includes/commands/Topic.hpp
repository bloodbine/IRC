#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Topic: public Command
{
private:
    /* data */
    Client* _client;
    size_t _size;
    std::string _channelName;
    std::string _topic;
	bool		_clearTopic;
	char *_out;
public:
    Topic(Client* client, const std::vector<std::string>& vec);
    void execute();
	int sendToClient() const;
    ~Topic();
};
