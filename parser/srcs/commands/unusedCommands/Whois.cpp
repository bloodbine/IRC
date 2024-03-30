#include "parser.hpp"

Whois::Whois(const std::vector<std::string>& cmd) : _user(""), _queryOperator(false)
{
	if (cmd.size() > 3) throw std::invalid_argument("Invalid syntax");
	if (cmd.size() >= 2)
	{
		if (isValidUserName(cmd[1])) _user = cmd[1];
		else throw std::invalid_argument("Invalid username syntax");
		if (cmd.size() == 3 && cmd[2].length() == 1 && cmd[2][0] == 'o') _queryOperator = true;
		else if (cmd.size() == 3) throw std::invalid_argument("Invalid mode");
	}
}

Whois::~Whois() {}

const std::string&	Whois::getUser() const { return _user; }
bool				Whois::getQueryOperator() const { return _queryOperator; }
