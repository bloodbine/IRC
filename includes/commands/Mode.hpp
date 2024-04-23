#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Mode: public Command
{
private:
    /* data */
    Client* _client;
    size_t _size;
    std::string _nickname;
    std::string _mode;
public:
    Mode(Client* client, const std::vector<std::string>& vec);
    char* execute() const;
    ~Mode();
};