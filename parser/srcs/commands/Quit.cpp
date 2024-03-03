#include "parser.hpp"

Quit::Quit(const std::vector<std::string>& cmd) : _message("")
{
	// // need to verify that cmd[1] syntax is valid for user or channel & set them accordingly
	// // need to check that cmd[2] startst with ':'
	if (cmd[1][0] != ':') throw std::invalid_argument("Invalid syntax");
	_message += cmd[1].substr(1);
	for (size_t i = 2; i < cmd.size(); i++) _message += " " + cmd[i];
}

Quit::~Quit() {}

const std::string&	Quit::getMessage() const { return _message; }
