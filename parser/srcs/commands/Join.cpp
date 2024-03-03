#include "parser.hpp"

Join::Join(const std::vector<std::string>& cmd) : _channel(""), _password("")
{
	if (cmd.size() < 2 || cmd.size() > 3) throw std::invalid_argument("Invalid syntax");
	if (cmd.size() >= 2)
	{
		if (isValidChannelName(cmd[1])) _channel = cmd[1].substr(1);
		else throw std::invalid_argument("Invalid syntax");
		if (cmd.size() == 3)
		{
			 if (cmd[2].length() > 50) std::invalid_argument("Invalid syntax");
			else _password = cmd[2];
		}
	}
}

Join::~Join() {}

const std::string&	Join::getChannel() const { return _channel; }
const std::string&	Join::getPassword() const { return _password; }
