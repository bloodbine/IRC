#pragma once

#include <iostream>
#include <string>

class List
{
private:
	std::string	_channel;
	bool		_channelExists;
public:
	List(const std::vector<std::string>& cmd);
	const std::string&	getChannel() const;
	bool				getChannelExists() const;
	~List();
};
