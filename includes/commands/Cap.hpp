#pragma once

#include "Command.hpp"
#include <vector>
#include <string>
#include <iostream>

class Cap : public Command
{
private:
	size_t	_size;
public:
	Cap(const std::vector<std::string>& vec);
	char*	execute() const;
	~Cap();
};