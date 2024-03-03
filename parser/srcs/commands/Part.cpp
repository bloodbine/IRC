#include "parser.hpp"

Part::Part(const std::vector<std::string>& cmd) : _channel(""), _reasson("")
{
	if (cmd.size() < 2) throw std::invalid_argument("Invalid syntax");
	
	if (isValidChannelName(cmd[1])) _channel = cmd[1].substr(1);
	else throw std::invalid_argument("Invalid syntax");

	// need to check that cmd[2] startst with ':'
	if (cmd.size() < 3 && cmd[2] == ":") throw std::invalid_argument("Invalid syntax");
	if (cmd[2][0] == ':')
	{
		// join in _reasson all from cmd[2](excluding ':') till cmd[n]
		_reasson += cmd[2].substr(1);
		for (size_t i = 3; i < cmd.size(); i++) _reasson += " " + cmd[i];
	}
}

Part::~Part() {}

const std::string&	Part::getChannel() const { return _channel; }
const std::string&	Part::getReasson() const { return _reasson; }
