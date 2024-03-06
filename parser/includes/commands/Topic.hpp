#pragma once

#include <iostream>
#include <string>

class Topic
{
private:
	std::string	_target;
	std::string	_message;
public:
	Topic(const std::vector<std::string>& cmd);
	const std::string&	getTarget() const;
	const std::string&	getMessage() const;
	~Topic();
};


