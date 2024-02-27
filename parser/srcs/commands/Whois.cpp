#include "Whois.hpp"

Whois::Whois(const std::string& text)
{
	if (text.length() > 103) throw std::invalid_argument("Too long string");
	std::vector<std::string>	tmp = split(text);
	if (tmp.size() != 2) throw std::invalid_argument("Invalid syntax");
	_target = tmp[1];
}
Whois::~Whois() {}

const std::string&				Whois::getTarget() const { return _target; }
