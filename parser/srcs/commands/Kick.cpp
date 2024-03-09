#include "parser.hpp"

Kick::Kick(const std::vector<std::string>& cmd) : _channel(""), _user(""), _message("")
{
	if (cmd.size() < 3) throw std::invalid_argument("invalid number of arguments");
	if (isValidChannelName(cmd[1]) == false) throw std::invalid_argument("invalid sintax");
	else _channel = cmd[1].substr(1);
	if (isValidUserName(cmd[2]) == false) throw std::invalid_argument("invalid sintax");
	else _user = cmd[2];
	if (cmd.size() > 3)
	{
		if (cmd[3][0] == ':')
		{
			// join in _message all from cmd[3](excluding ':') till cmd[n]
			_message += cmd[3].substr(1);
			for (size_t i = 4; i < cmd.size(); i++) _message += " " + cmd[i];
		}
	}
}

Kick::~Kick() {}

const std::string&	Kick::getChannel() const { return _channel; }
const std::string&	Kick::getUser() const { return _user; }
const std::string&	Kick::getMessage() const { return _message; }
