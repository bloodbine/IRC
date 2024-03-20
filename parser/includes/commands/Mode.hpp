#pragma once

#include <iostream>
#include <string>

class Mode
{
private:
	std::string	_target;
	std::string	_mode;
	std::string	_optional;
public:
	Mode(const std::vector<std::string>& cmd);
	const std::string&	getTarget() const;
	const std::string&	getMode() const;
	const std::string&	getOptional() const;
	~Mode();
};


