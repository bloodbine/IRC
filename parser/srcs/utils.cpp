#include "parser.hpp"

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

std::vector<std::string>	split(const std::string& text)
{
	std::vector<std::string>	out;
	std::stringstream			ss(text);
	std::string					word;

	if (text == "") out.push_back("");
	else
	{
		while (ss >> word) out.push_back(word);
	}
	return out;
}
