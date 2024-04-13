#include "commands/Nick.hpp"
#include "server.hpp"

// char* Nick::ERR_NONICKNAMEGIVEN(const std::string& serverIp) const
// {
// 	std::string tmp = serverIp;
// 	tmp += " 431 :No nickname given\n";
// 	char	*out = new char[tmp.size() + 1];
// 	std::strcpy(out, tmp.c_str());
// 	return (out);
// }
// //            ERR_NICKNAMEINUSE
// //            ERR_RESTRICTED

// char*	Nick::ERR_ERRONEUSNICKNAME(const std::string& serverIp) const
// {
// 	std::string tmp = serverIp;
// 	tmp += " " +  _vec[0];
// 	tmp += " 432 :Erroneous nickname\n";
// 	char	*out = new char[tmp.size() + 1];
// 	std::strcpy(out, tmp.c_str());
// 	return (out);
// }

// char*	Nick::ERR_NICKNAMEINUSE(const std::string& serverIp) const
// {
// 	std::string tmp = serverIp;
// 	tmp += " " + _vec[0];
// 	tmp += " 433 :Nickname is already in use\n";
// 	char	*out = new char[tmp.size() + 1];
// 	std::strcpy(out, tmp.c_str());
// 	return (out);
// }

Nick::Nick(Client& client, const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec), _client(client) {}

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

char*	Nick::execute() const
{
	char	*out;
	if (_client.getIsValidatedPassword() == false)
	{
		std::string tmp = "You need to add run first PASS!\n";
		out = new char[tmp.size() + 1];
		std::strcpy(out, tmp.c_str());
	}
	// else if (_size == 1) out = ERR_NONICKNAMEGIVEN(serverIp);
	// else if (_size == 2) {
	// 	if (client.GetNickName() == _vec[1]) out = ERR_NICKNAMEINUSE(serverIp);
	// 	else if (validNick() == false) out = ERR_ERRONEUSNICKNAME(serverIp);
	// 	else
	// 	{
	// 		client.setNickName(_vec[1]);
	// 		std::string tmp = "Nick set to: " + _vec[1] + "\n";
	// 		out = new char[tmp.size() + 1];
	// 		std::strcpy(out, tmp.c_str());
	// 	}
	// }
	else out = NULL;
	std::cout << out << std::endl;
	return out;
}
Nick::~Nick() {}