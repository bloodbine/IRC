#include "parser.hpp"

Who::Who(const std::vector<std::string>& cmd) : _channel(""), _queryOperator(false)
{
	if (cmd.size() > 3) throw std::invalid_argument("Invalid syntax");
	if (cmd.size() >= 2)
	{
		if (isValidChannelName(cmd[1])) _channel = cmd[1].substr(1);
		else throw std::invalid_argument("Invalid channel syntax");
		if (cmd.size() == 3 && cmd[2].length() == 1 && cmd[2][0] == 'o') _queryOperator = true;
		else if (cmd.size() == 3) throw std::invalid_argument("Invalid mode");
	}
}

Who::~Who() {}

const std::string&	Who::getChannel() const { return _channel; }
bool				Who::getQueryOperator() const { return _queryOperator; }
