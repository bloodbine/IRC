#include "commands/Shutdown.hpp"
#include "server.hpp"

Shutdown::Shutdown(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	(void)_client;
	if (_size > 1) _password = vec[1];
	if (_size != 2 || _password != "hola") throw std::invalid_argument("462 :Password incorrect\r\n");
}

char*	Shutdown::execute() const
{
	return NULL;
}

Shutdown::~Shutdown() {}