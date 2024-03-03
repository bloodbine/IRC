#pragma once

#include <iostream>
#include <string>

class Part
{
private:
	std::string	_channel;
	std::string	_reasson;
public:
	Part(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	const std::string&	getReasson() const;
	~Part();
};


