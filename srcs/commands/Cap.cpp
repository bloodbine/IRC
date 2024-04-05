#include "commands/Cap.hpp"

Cap::Cap(const std::vector<std::string>& vec) : _size(vec.size()) {}

char*	Cap::execute() const
{
	std::string tmp = "PONG 127.0.0.1";
	char		*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return out;
}
Cap::~Cap() {}