#include "commands/Nick.hpp"
#include "server.hpp"

char* Nick::ERR_NONICKNAMEGIVEN(const std::string& serverIp) const
{
	std::string tmp = serverIp;
	tmp += "\t431 :No nickname given\n";
	char	*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return (out);
}
//            ERR_NICKNAMEINUSE
//            ERR_RESTRICTED

char*	Nick::ERR_ERRONEUSNICKNAME(const std::string& serverIp) const
{
	std::string tmp = serverIp;
	tmp += " 431 :No nickname given\n";
	char	*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return (out);
}

Nick::Nick(const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec) {}

bool	Nick::validNick() const
{
	if (_vec[1].size() > 1 && _vec[1].size() <= 9)
	{
		if (isSpecialChar(_vec[1][0]) || std::isalpha(_vec[1][0]))
		{
			std::string::const_iterator i = _vec[1].begin();
			i++;
			for (; i != _vec[1].end(); ++i)
			{
				if (isSpecialChar(*i) || std::isalnum(*i) || *i == '-')
					continue;
				return false;
			}
			return true;
		}
		return false;
	}
	return false;
}

char*	Nick::execute(server& Server) const
{
	char	*out;
	const std::string serverIp = Server.getServerIp();

	if (_size == 1) out = ERR_NONICKNAMEGIVEN(serverIp);
	else if (_size == 2) {
		if (validNick() == false) out = ERR_ERRONEUSNICKNAME(serverIp);
		else
		{
			std::string tmp = "Nick set to: " + _vec[1] + "\n";
			out = new char[tmp.size() + 1];
			std::strcpy(out, tmp.c_str());
		}
	}
	else out = NULL;
	std::cout << out << std::endl;
	return out;
}
Nick::~Nick() {}