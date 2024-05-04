#include "commands/Nick.hpp"
#include "server.hpp"

Nick::Nick(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\r\n");
	_nickName = vec[1];
	if (_size > 2 || (_size == 2 && !validNick(vec[1]))) ERR_ERRONEUSNICKNAME(vec[1]);
	if (_client->getNickName() == vec[1]) ERR_NICKNAMEINUSE(vec[1]);
	_nickName = vec[1];
}

std::string	Nick::execute() const
{
	if (server::clientExists(_nickName)) ERR_ALREADYREGISTRED();
	_client->setNickName(_nickName);
	std::string	out = "NICK " + _nickName + "\r\n";
	return out;
}
Nick::~Nick() {}