#include "parser.hpp"

bool	isValidChannelName(const std::string& name)
{

	if ((name[0] == '#' || name[0] == '&') && isValidUserName(name.substr(1))) return true;
	return false;
}
