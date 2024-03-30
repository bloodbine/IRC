#pragma once

#include <iostream>
#include <string>

class Who
{
private:
	std::string	_channel;
	bool		_queryOperator;
public:
	Who(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	bool				getQueryOperator() const;
	~Who();
};
