#include "parser.hpp"

static bool	isValidUserName(const std::string& name)
{
	std::string::const_iterator it = name.begin();
	std::string::const_iterator end = name.end();
	int							i = 0;

	if (name.length() > 50) return false;
	for (; it != end; ++it)
	{
		if (i == 0 && std::isdigit(*it)) return false;
		if (*it != '_' && !std::isalnum(*it)) return false;
		i++;
	}
	
	return true;
}

static bool	isValidChannelName(const std::string& name)
{

	if ((name[0] == '#' || name[0] == '&') && isValidUserName(name.substr(1))) return true;
	return false;
}

static	bool isValidHalfCmd(const std::string& text)
{
	std::vector<std::string> cmd = split(text);

	if (cmd.size() != 2) return false;
	if (!isValidUserName(cmd[1])) return isValidChannelName(cmd[1]);
	return true;
}

bool	isValidPrivmsg(const std::string& text)
{
	size_t halfCmdIndex = text.find(':');

	if (halfCmdIndex == std::string::npos) return false;
	std::string halfCmd = text.substr(0, halfCmdIndex);
	if (isValidHalfCmd(halfCmd) == false) return false;
	std::string message = text.substr(halfCmdIndex + 1);
	if (message.length() <= 0)	return false;
	return true;
}
