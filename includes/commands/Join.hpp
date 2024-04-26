#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Join: public Command
{
private:
    /* data */
    Client* _client;
    size_t _size;
    std::string _channelName;
	std::string _chanKey;
public:
    Join(Client* client, const std::vector<std::string>& vec);
    char* execute() const;
    ~Join();
};
