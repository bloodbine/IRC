#pragma once

#include <iostream>
#include <string>

class Nick
{
private:
	std::string	_user;
public:
	Nick(const std::vector<std::string>& cmd);
	~Nick();
	const std::string&	getUser() const;
};

