#include "parser.hpp"

List::List(const std::vector<std::string>& cmd) : _channel(""), _channelExists(false)
{
	if (cmd.size() != 1 && cmd.size() != 2) throw std::invalid_argument("Invalid syntax");
	if (cmd.size() == 2)
	{
		if (isValidChannelName(cmd[1])) _channel = cmd[1].substr(1);
		else throw std::invalid_argument("Invalid channel syntax");
		_channelExists = true;
	}
}

List::~List() {}

const std::string&	List::getChannel() const { return _channel; }
bool				List::getChannelExists() const { return _channelExists; }
