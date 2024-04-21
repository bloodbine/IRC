#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Part: public Command
{
private:
    /* data */
    Client* _client;
    size_t _size;
    std::string _channelName;
	char *_out;
public:
    Part(Client* client, const std::vector<std::string>& vec);
    void execute();
	int sendToClient() const;
    ~Part();
};
