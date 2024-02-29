#include "parser.hpp"

Nick::Nick(const std::vector<std::string>& cmd) : _user("")
{
	if (cmd.size() != 2) throw std::invalid_argument("Invalid syntax");
	if (cmd[1].length() < 4) throw std::invalid_argument("Password too short");
	if (cmd[1].length() > 53) throw std::invalid_argument("Password too long");
	_user = cmd[1];
}

Nick::~Nick() {}

const std::string&	Nick::getUser() const { return _user; }
