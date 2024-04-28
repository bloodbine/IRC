#include "commands/Shutdown.hpp"
#include "server.hpp"

Shutdown::Shutdown(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\r\n");
	_password = vec[1];
	if (_size > 2 || _password != "hola") throw std::invalid_argument("Invalid Password!");
}

char*	Shutdown::execute() const
{
	return NULL;
}

Shutdown::~Shutdown() {}