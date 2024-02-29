#include "parser.hpp"

Privmsg::Privmsg(const std::vector<std::string>& cmd) : _target(""), _hasUser(false), _message("")
{
	if (cmd.size() < 3) throw std::invalid_argument("Invalid syntax");
	
	// need to verify that cmd[1] is valid user or channel
	// need to check that cmd[2] startst with ':'
	// join in _message all from cmd[2] till cmd[n]
}

Privmsg::~Privmsg()
{
}

const std::string&	Privmsg::getTarget() const { return _target; }
const std::string&	Privmsg::getMessage() const { return _message; }
bool				Privmsg::getHasUser() const { return _hasUser; }
