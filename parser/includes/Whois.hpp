#pragma once

#include "parser.hpp"

class Whois
{
private:
	std::string	_target;
public:
	Whois(const std::string& text);
	~Whois();
	const std::string&	getTarget() const;
};

