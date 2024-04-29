#include "commands/Ping.hpp"
#include "server.hpp"

Ping::Ping(Client* client, const std::vector<std::string>& vec) : _size(vec.size())
{
	(void)client;
	if (_size == 1) ERR_NOORIGIN();
	// if (_size > 3) ERR_NOSUCHSERVER(vec[3]);
	if (_size == 2) _serverName = vec[1];
	if (_size >= 3) _serverName = vec[2];
	if (std::find(vec.begin(), vec.end(), "ircserv") != vec.end()) _serverName = "ircserv";
}

std::string	Ping::execute() const
{
	std::string	out = "PONG :" + _serverName + "\r\n";
	return out;
}
Ping::~Ping() {}