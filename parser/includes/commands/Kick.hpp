#pragma once

#include <iostream>
#include <string>

class Kick
{
private:
	std::string	_channel;
	std::string	_user;
	std::string	_message;
public:
	Kick(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	const std::string&	getUser() const;
	const std::string&	getMessage() const;
	~Kick();
};
