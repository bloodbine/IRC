#include "parser.hpp"

Invite::Invite(const std::vector<std::string>& cmd) : _channel(""), _user("")
{
	(void)cmd;
	if (cmd.size() < 3) throw std::invalid_argument("invalid number of arguments");
	if (isValidChannelName(cmd[1]) == false) throw std::invalid_argument("invalid sintax");
	else _channel = cmd[1].substr(1);
	if (isValidUserName(cmd[2]) == false) throw std::invalid_argument("invalid sintax");
	else _user = cmd[2];
}

Invite::~Invite() {}

const std::string&	Invite::getChannel() const { return _channel; }
const std::string&	Invite::getUser() const { return _user; }
