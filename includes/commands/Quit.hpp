#pragma once 

#include <iostream>
#include "Command.hpp"
#include "server.hpp"
#include "Client.hpp"

class server;
class Quit: public Command
{
private:
    /* data */
    Client* _client;
    size_t _size;
    std::string _reasson;
public:
    Quit(Client* client, const std::vector<std::string>& vec);
    char* execute() const;
    ~Quit();
};
