#include "parser.hpp"

Pass::Pass(const std::vector<std::string>& cmd) : _password("")
{
	(void)cmd;
	if (cmd.size() != 2) throw std::invalid_argument("Invalid syntax");
	if (cmd[1].length() < 4) throw std::invalid_argument("Password too short");
	if (cmd[1].length() > 53) throw std::invalid_argument("Password too long");
	_password = cmd[1];
}

Pass::~Pass() {}

const std::string&	Pass::getPassword() const { return _password; }
