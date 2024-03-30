#pragma once

#include <iostream>
#include <string>

class Whois
{
private:
	std::string	_user;
	bool		_queryOperator;
public:
	Whois(const std::vector<std::string>& cmd);
	const std::string&	getUser() const;
	bool				getQueryOperator() const;
	~Whois();
};
