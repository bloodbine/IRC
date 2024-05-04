#include "commands/Cap.hpp"
#include "server.hpp"

Cap::Cap(Client* client, const std::vector<std::string>& vec) : _size(vec.size()), _client(client), _serverAddress("127.0.0.1")
{
	if (_size != 4) throw std::invalid_argument("Invalid CAP negociation");
	else _serverAddress = vec[3].substr(1);
}

std::string	Cap::execute() const
{
	(void)_client;
	std::string tmp = "PONG " + _serverAddress + "\r\n";
	return tmp;
}
Cap::~Cap() {}