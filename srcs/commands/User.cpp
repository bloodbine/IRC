#include "commands/User.hpp"
#include "server.hpp"
User::User(const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec), _userName("") {}

bool	User::validUser() const
{
	std::string	invalid = "\x00\x0A\x0D\x20\x40";
	if (_size < 5 || _size > 8) return false;
	if (_vec[1].size() > 1 && _vec[1].size() <= 9)
	{
		std::string::const_iterator end = _vec[1].end();
		for (std::string::const_iterator itr = _vec[1].begin(); itr != end; ++itr)
			if (invalid.find(*itr) != std::string::npos) return false;
	}
	/*
	Still to implement the mode and the ip.
	*/
	if (_vec[3] != "*") return false;
	return true;
}

char*	User::execute(server& server, Client& client) const
{
	char	*out = NULL;
	const std::string serverIp = server.getServerIp();

	if (client.GetNickName() == "")
	{
		std::string tmp = "You need to set NICK <nickname>!\n";
		out = new char[tmp.size() + 1];
		std::strcpy(out, tmp.c_str());
	}
	else
	{
		if (validUser() == true)
		{
			// set client.setUsername() to username.
			client.setUserName(_vec[1]);
			std::string realName = "";
			for (size_t i = 4; i < _size; i++) realName += _vec[i];
			client.setRealUserName(realName);
			// set client.setMode() to mode.
			// set realName
		}
	}
	std::cout << out << std::endl;
	return out;
}
User::~User() {}