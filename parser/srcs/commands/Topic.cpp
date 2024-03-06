#include "parser.hpp"

Topic::Topic(const std::vector<std::string>& cmd) : _target(""), _message("")
{
	if (cmd.size() < 3) throw std::invalid_argument("Invalid syntax");
	
	// // need to verify that cmd[1] syntax is valid for user or channel & set them accordingly
	if (isValidChannelName(cmd[1])) _target = cmd[1].substr(1);
	else throw std::invalid_argument("Invalid syntax");

	// // need to check that cmd[2] startst with ':'
	if (cmd.size() <= 3 && cmd[2] == ":") throw std::invalid_argument("Invalid syntax");
	if (cmd[2][0] == ':')
	{
		// join in _message all from cmd[2](excluding ':') till cmd[n]
		_message += cmd[2].substr(1);
		for (size_t i = 3; i < cmd.size(); i++) _message += " " + cmd[i];
	}
}

Topic::~Topic() {}

const std::string&	Topic::getTarget() const { return _target; }
const std::string&	Topic::getMessage() const { return _message; }
