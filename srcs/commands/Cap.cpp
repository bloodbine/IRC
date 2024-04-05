#include "commands/Cap.hpp"

Cap::Cap(const std::vector<std::string>& vec) : _size(vec.size())
{
	if (_size != 4) _serverAddress = "127.0.0.1";
	else _serverAddress = vec[3].substr(1);
}

char*	Cap::execute() const
{
	std::string tmp = "PONG " + _serverAddress;
	char		*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return out;
}
Cap::~Cap() {}