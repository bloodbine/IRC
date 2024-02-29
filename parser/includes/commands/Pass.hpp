#pragma once

#include <iostream>
#include <string>

class Pass
{
private:
	std::string	_password;
public:
	Pass(const std::vector<std::string>& cmd);
	const std::string&	getPassword() const;
	~Pass();
};

