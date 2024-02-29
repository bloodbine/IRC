#include"parser.hpp"

bool	isValidUserName(const std::string& name)
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
