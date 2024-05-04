#pragma once

#include <string>
#include <vector>

class server;
class Client;

class Command
{
private:
	Client*	_client;
	std::vector<std::string>	_vec;
	size_t	_size;
	int	_cmdType;
	std::string	_stringToSend;
public:
	Command(const std::vector<std::string>& vec, Client *client);
	void	handlePass();
	void	handleNick();
	~Command();
};