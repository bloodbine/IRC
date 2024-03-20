#include "parser.hpp"

bool	isValidSet(char mode, size_t len)
{
	if (len == 4 && (mode == 'o' || mode == 'k')) return true;
	if (len == 3 && (mode == 'i' || mode == 't' || mode == 'l')) return true;
	return false;
}

bool	isValidRemove(char mode, size_t len)
{
	if (len == 4 && mode == 'o') return true;
	if (len == 3 && (mode != 'i' || mode != 't' || mode != 'l' || mode != 'k')) return true;
	return false;
}

bool	isValidModeCmd(const std::vector<std::string>& vec)
{
	size_t	len = vec.size();
	char	mode;
	
	if (len < 3) return false;
	mode = vec[2][1];
	if (vec[2][0] != '+' && vec[2][0] != '-') return false;
	if (vec[2][0] == '+' && !isValidSet(mode, len)) return false;
	if (vec[2][0] == '-' && !isValidRemove(mode, len)) return false;
	if (len != 4 && len != 3) return false;
	return true;
}