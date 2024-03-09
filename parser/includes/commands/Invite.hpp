#pragma once

#include <iostream>
#include <string>

class Invite
{
private:
	std::string	_channel;
	std::string	_user;
public:
	Invite(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	const std::string&	getUser() const;
	~Invite();
};
