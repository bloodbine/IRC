#pragma once

#include <iostream>
#include <string>

class Cmd
{
public:
	Cmd() {}
	virtual ~Cmd() {}
	virtual const std::string&	getTarget() const = 0;
	virtual const std::string&	getMessage() const = 0;
	virtual bool				getHasUser() const = 0;
};
