#include "commands/User.hpp"
#include "server.hpp"

User::User(Client& client, const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec), _userName(""), _client(client) {}

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
	if (_vec[3] != "*") return true;
	return true;
}

char*	User::execute() const
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
			std::string realName = "";
			for (size_t i = 4; i < _size; i++) 
			{
				if (i > 4)
					realName += " " + _vec[i];
				else realName += _vec[i];
			}
			client.setUserName(_vec[1]);
			client.setRealUserName(realName);
			client.setIsRegistered();
			// set client.setMode() to mode.
			// set realName
			std::string tmp = "NOW YOU ARE REGISTERED!\n";
			out = new char[tmp.size() + 1];
			std::strcpy(out, tmp.c_str());
		}
		else
		{
			std::string tmp = "INVALID USER SINTAX!\n";
			out = new char[tmp.size() + 1];
			std::strcpy(out, tmp.c_str());
		}
	}
	
	return out;
}
User::~User() {}