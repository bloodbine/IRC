#pragma once

#include "parser.hpp"

class Pass
{
private:
	std::string	_password;
public:
	Pass(const std::string& text);
	~Pass();
	const std::string&	getPassword() const;
};

