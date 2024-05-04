#include "commands/Ping.hpp"
#include "server.hpp"

Ping::Ping(Client* client, const std::vector<std::string>& vec) : _size(vec.size())
{
	_client = client;
	if (_size == 1) ERR_NOORIGIN();
	// if (_size > 3) ERR_NOSUCHSERVER(vec[3]);
	if (_size == 2) _serverName = vec[1];
	else
	{
		// _serverName = vec[2];
		for (unsigned int i = 2; i < vec.size(); ++i)
		{
			if (i != vec.size() - 1)
				_serverName += vec[i] + " ";
			else
				_serverName += vec[i];
		}
	}
}

std::string	Ping::execute() const
{
	std::string	out = "PONG " + _client->getNickName() + " " + _serverName + "\r\n";
	std::cout << out;
	return out;
}
Ping::~Ping() {}