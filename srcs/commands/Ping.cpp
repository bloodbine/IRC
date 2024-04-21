#include "commands/Ping.hpp"
#include "server.hpp"

Ping::Ping(Client* client, const std::vector<std::string>& vec) : _size(vec.size()), _client(client)
{
	if (_size == 1) ERR_NOORIGIN();
	// MISSING ERR_NOSUCHSERVER
	if (_size == 2 && (vec[1] != "localhost" && vec[1] != "127.0.0.1")) ERR_NOSUCHSERVER(vec[1]);
	if (_size == 3 && (vec[2] != "localhost" && vec[2] != "127.0.0.1")) ERR_NOSUCHSERVER(vec[2]);
	if (_size > 3) ERR_NOSUCHSERVER(vec[3]);
	if (_size == 2) _serverName = vec[1];
	if (_size == 3) _serverName = vec[2];
}

void Ping::execute()
{
	std::string	out = "PONG " + _serverName;
	_out = strdup(out.c_str());
}

int Ping::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}

Ping::~Ping() {}