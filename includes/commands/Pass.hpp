#pragma once

#include "Command.hpp"
#include <iostream>
#include "server.hpp"

class server;
class Pass : public Command
{
private:
    /* data */
    std::string _password;
public:
    Pass(const std::vector<std::string>& vec);
    char* execute(server& server, Client& client) const;
    ~Pass();
};

