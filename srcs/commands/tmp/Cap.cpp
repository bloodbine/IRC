#include "commands/Cap.hpp"
#include "server.hpp"

Cap::Cap(Client& client, const std::vector<std::string>& vec) : _size(vec.size()), _client(client)
{
	else _serverAddress = vec[3].substr(1);
}

char*	Cap::execute() const
{
	std::string tmp = "PONG localhost" + "\n";
	char		*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return out;
}
Cap::~Cap() {}