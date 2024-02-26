#pragma once

#include "parser.hpp"

class Privmsg
{
private:
	bool		_targetIsUser;
	std::string	_target;
	std::string	_message;
public:
	Privmsg(const std::string& text);
	~Privmsg();
	bool	getTargetIsUser() const;
	const std::string&	getTarget() const;
	const std::string&	getMessage() const;
};
