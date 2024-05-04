#pragma once

#include <string>
class server;
class Client;

class Command
{
private:
	Client*	_client;
	int	_cmdType;
	std::string	_stringToSend;
public:
	Command(const std::vector<std::string>& vec, Client *client);
	void execute();
	~Command();
};