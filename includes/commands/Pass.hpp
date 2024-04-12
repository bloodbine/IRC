#pragma once

#define ERR_ALREADYREGISTRED 462
#define ERR_PASSWDMISMATCH 464 

#include "Command.hpp"
#include <iostream>
#include "server.hpp"
#include "Client.hpp"

class server;
class Pass : public Command
{
private:
    std::string _password;
public:
    Pass(const std::vector<std::string>& vec);
    char* execute(server& server, Client& client) const;
    std::string errorMessage(int errorCode) const;
    ~Pass();
};
