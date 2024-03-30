#pragma once

#include "commands.hpp"

class Pass
{
private:
	std::string	_password;
public:
	Pass(const std::vector<std::string>& cmd);
	const std::string&	getPassword() const;
	~Pass();
};

