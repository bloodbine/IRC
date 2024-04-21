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

void	User::execute()
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
	if (server::getClientFdByNickName(_vec[1]) == -1) ERR_ALREADYREGISTRED();
	else server::addClient(_client);
	// set client.setMode() to mode.
	std::cout << "Does 'hola' channel exists: " << server::channelExists("hola") << std::endl;
	std::cout << "Does 'mundo' channel exists: " << server::channelExists("mundo") << std::endl;
	std::string out = "001 * Welcome to the Internet Relay Network " + _client->GetNickName() + "!" + _client->GetUserName() +"@127.0.0.1\n";
	_out = strdup(out.c_str());
}

int User::sendToClient() const
{
	int	fdToSend = _client->getFd();
	std::cout << "Sending to the client: " << _out << std::endl;
	return (send(fdToSend, _out, std::strlen(_out), 0));
}


User::~User() {}