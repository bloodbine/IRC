#pragma once

#include <iostream>
#include <string>

class Join
{
private:
	std::string	_channel;
	std::string	_password;
public:
	Join(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	const std::string&	getPassword() const;
	~Join();
};


