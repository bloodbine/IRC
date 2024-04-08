#include "commands/Cap.hpp"
#include "server.hpp"

Cap::Cap(const std::vector<std::string>& vec) : _size(vec.size())
{
	if (_size != 4) _serverAddress = "127.0.0.1";
	else _serverAddress = vec[3].substr(1);
}

char*	Cap::execute(server& server, Client& client) const
{
	(void) client;
	std::string tmp = "PONG " + _serverAddress + "\n";
	char		*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	server.setServerIp(_serverAddress);
	std::cout << "set ip: " << _serverAddress << std::endl;
	return out;
}
Cap::~Cap() {}