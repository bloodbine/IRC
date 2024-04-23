#include "commands/Nick.hpp"
#include "server.hpp"

Nick::Nick(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\n");
	_nickName = vec[1];
	if (_size > 2 || (_size == 2 && !validNick(vec[1]))) ERR_ERRONEUSNICKNAME(vec[1]);
	if (_client->GetNickName() == vec[1]) ERR_NICKNAMEINUSE(vec[1]);
	_nickName = vec[1];
}

char*	Nick::execute() const
{
	_client->setNickName(_nickName);
	std::string	out = "NICK " + _nickName + "\n";
	return strdup(out.c_str());
}
Nick::~Nick() {}