#include "commands/Cap.hpp"
#include "server.hpp"

Cap::Cap(Client* client, const std::vector<std::string>& vec) : _size(vec.size()), _client(client), _serverAddress("127.0.0.1")
{
	if (_size != 4) throw std::invalid_argument("Invalid CAP negociation");
	else _serverAddress = vec[3].substr(1);
}

void	Cap::execute()
{
	std::string tmp = "PONG " + _serverAddress + "\n";
	_out = strdup(tmp.c_str());
}

int Cap::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}

Cap::~Cap() {}