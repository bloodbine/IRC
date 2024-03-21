#pragma once

#include "commands.hpp"
#include "Cmd.hpp"

class Privmsg : public Cmd
{
private:
	std::string	_target;
	bool		_hasUser;
	std::string	_message;
public:
	Privmsg(const std::vector<std::string>& cmd);
	const std::string&	getTarget() const;
	const std::string&	getMessage() const;
	bool				getHasUser() const;
	~Privmsg();
};


