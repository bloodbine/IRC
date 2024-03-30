#include "parser.hpp"

Motd::Motd(const std::vector<std::string>& cmd) : _channel("")
{
	if (cmd.size() != 1 && cmd.size() != 2) throw std::invalid_argument("Invalid syntax");
	if (cmd.size() >= 2)
	{
		if (isValidChannelName(cmd[1])) _channel = cmd[1].substr(1);
		else throw std::invalid_argument("Invalid channel syntax");
	}
}

Motd::~Motd() {}

const std::string&	Motd::getChannel() const { return _channel; }
