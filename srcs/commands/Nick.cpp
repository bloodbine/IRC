#include "commands/Nick.hpp"
#include "server.hpp"

Nick::Nick(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\n");
	_nickName = vec[1];
	if (_size > 2 || (_size == 2 && !validNick(vec[1]))) throw std::invalid_argument(" 432 :Erroneous nickname\n");
	if (_client->GetNickName() == vec[1]) throw std::invalid_argument(" 433 :Nickname is already in use\n");
	_nickName = vec[1];
}

char*	Nick::execute() const
{
	if (validNick(_nickName)) _client->setNickName(_nickName);
	else throw std::invalid_argument(" 432 :Erroneous nickname\n");
	std::string	out = "NICK " + _nickName + "\n";
	return strdup(out.c_str());
}
Nick::~Nick() {}