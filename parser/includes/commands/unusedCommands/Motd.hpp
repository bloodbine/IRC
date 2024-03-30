#pragma once

#include <iostream>
#include <string>

class Motd
{
private:
	std::string	_channel;
public:
	Motd(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	~Motd();
};
