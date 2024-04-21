#pragma once

#include "Command.hpp"
#include <iostream>
#include "server.hpp"
#include "Client.hpp"

class server;
class Pass : public Command
{
private:
    Client      *_client;
    std::string _password;
	char *_out;
public:
    Pass(Client* client, const std::vector<std::string>& vec);
    void execute();
	int sendToClient() const;
    ~Pass();
};
