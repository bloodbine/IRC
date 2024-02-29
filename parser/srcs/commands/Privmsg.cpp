#include "parser.hpp"

Privmsg::Privmsg(const std::vector<std::string>& cmd) : _target(""), _hasUser(false), _message("")
{
	if (cmd.size() < 3) throw std::invalid_argument("Invalid syntax");
	
	// need to verify that cmd[1] syntax is valid for user or channel & set them accordingly
	if (isValidUserName(cmd[1]) && (_hasUser = true))  _target = cmd[1];
	else if (isValidChannelName(cmd[1])) _target = cmd[1].substr(1);
	else throw std::invalid_argument("Invalid syntax");

	// need to check that cmd[2] startst with ':'
	if (cmd.size() <= 3 && cmd[2] == ":") throw std::invalid_argument("Invalid syntax");
	if (cmd[2][0] == ':')
	{
		_message += cmd[2].substr(1);
		for (size_t i = 3; i < cmd.size(); i++) _message += " " + cmd[i];
	}
	// join in _message all from cmd[2] till cmd[n]
}

Privmsg::~Privmsg()
{
}

const std::string&	Privmsg::getTarget() const { return _target; }
const std::string&	Privmsg::getMessage() const { return _message; }
bool				Privmsg::getHasUser() const { return _hasUser; }
