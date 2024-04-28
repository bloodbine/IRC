#include "commands/User.hpp"
#include "server.hpp"

User::User(Client* client, const std::vector<std::string>& vec) : _size(vec.size()), _vec(vec), _userName(""), _client(client)
{
	// if (_client->getIsValidatedPassword() == false) missingPass();
	if (_client->GetIsRegistered()) ERR_ALREADYREGISTRED();
	if (_client->GetNickName() == "") missingNick();
	if (_size < 5) ERR_NEEDMOREPARAMS("USER");
	if (validUser() == false) ERR_SYNTAXPROBLEM();

}

bool	User::validUser() const
{
	std::string	invalid = "\x00\x0A\x0D\x20\x40";
	if (_size < 5 || _size > 7) return false;
	if (_vec[1].size() > 1 && _vec[1].size() <= 9)
	{
		std::string::const_iterator end = _vec[1].end();
		for (std::string::const_iterator itr = _vec[1].begin(); itr != end; ++itr)
			if (invalid.find(*itr) != std::string::npos) return false;
	}
	if (_vec[2] != "0") return false;
	if (_vec[3] != "*") return false;
	if (_vec[4].size() < 2) return false;
	return true;
}

char*	User::execute() const
{

	std::string realName = "";
	if (_vec[4][0] == ':') realName = _vec[4].substr(1);
	else realName = _vec[4];
	for (size_t i = 5; i < _size; i++) 
	{
			realName += " " + _vec[i];
	}
	_client->setUserName(_vec[1]);
	_client->setRealUserName(realName);
	_client->setIsRegistered();
	if (server::clientExists(_vec[1])) ERR_ALREADYREGISTRED();
	else server::addClient(_client);
	// set client.setMode() to mode.
	std::cout << "Username\t|\tReal Name" << std::endl;
	std::cout << _client->GetUserName() << "\t\t|" << _client->GetRealUserName() << std::endl;
	std::string out = ":" + server::getHostname() + " 001 " + _client->GetNickName() + " :Welcome to the 42 Heilbronn KVIRC Network, " + _client->GetNickName() + "!" + _client->GetUserName() + "@" + server::getHostname() + "\r\n";
	out += ":" + server::getHostname() + " 002 " + _client->GetNickName() + " :Your host is KVIRC, running version 5.0\r\n";
	out += ":" + server::getHostname() + " 003 " + _client->GetNickName() + " :This server was created " + server::getCreationTime() + "\r\n";
	out += ":" + server::getHostname() + " 004 " + _client->GetNickName() + " :KVIRC 5.0 itkol\r\n";
	return strdup(out.c_str());
}

User::~User() {}