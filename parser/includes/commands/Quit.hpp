#pragma once

#include <iostream>
#include <string>

class Quit
{
private:
	std::string	_message;
public:
	Quit(const std::vector<std::string>& cmd);
	const std::string&	getMessage() const;
	~Quit();
};


