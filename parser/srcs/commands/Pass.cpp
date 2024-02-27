#include "Pass.hpp"

Pass::Pass(const std::string& text)
{
	if (text.length() > 54) throw std::invalid_argument("Too long string");
	std::vector<std::string>	tmp = split(text);
	if (tmp.size() != 2) throw std::invalid_argument("Invalid syntax");
	_password = tmp[1];
}
Pass::~Pass() {}

const std::string&				Pass::getPassword() const { return _password; }
