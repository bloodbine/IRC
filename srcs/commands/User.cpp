#include "commands/User.hpp"
#include "server.hpp"

User::User(Client* client, const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec), _userName(""), _client(client)
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_client->GetIsRegistered()) ERR_ALREADYREGISTRED();
	if (_client->GetNickName() == "") missingNick();
	if (_size < 5) ERR_NEEDMOREPARAMS("USER");
	if (validUser() == false) throw std::invalid_argument("INVALID SYNTAX");

}

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

	std::string realName = "";
	for (size_t i = 4; i < _size; i++) 
	{
		if (i > 4)
			realName += " " + _vec[i];
		else realName += _vec[i];
	}
	_client->setUserName(_vec[1]);
	_client->setRealUserName(realName);
	_client->setIsRegistered();
	// set client.setMode() to mode.
	std::cout << "Does 'hola' channel exists: " << server::channelExists("hola") << std::endl;
	std::cout << "Does 'mundo' channel exists: " << server::channelExists("mundo") << std::endl;
	return strdup("NOW YOU ARE REGISTERED!\n");
}

User::~User() {}