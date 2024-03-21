#pragma once

#include "commands.hpp"
#include "Cmd.hpp"

class Pass : public Cmd
{
private:
	std::string	_password;
public:
	Pass(const std::vector<std::string>& cmd);
	const std::string&	getPassword() const;
	~Pass();
};

