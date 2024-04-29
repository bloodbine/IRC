#include "commands/Ping.hpp"
#include "server.hpp"

Ping::Ping(Client* client, const std::vector<std::string>& vec) : _size(vec.size())
{
	(void)client;
	if (_size == 1) ERR_NOORIGIN();
	// MISSING ERR_NOSUCHSERVER
	if (_size > 3) ERR_NOSUCHSERVER(vec[3]);
	if (_size == 2) _serverName = vec[1];
	if (_size == 3) _serverName = vec[2];
}

std::string	Ping::execute() const
{
	std::string	out = "PONG " + _serverName;
	return out;
}
Ping::~Ping() {}