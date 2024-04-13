#include "commands/Nick.hpp"
#include "server.hpp"

Nick::Nick(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) throw std::invalid_argument(" ERROR: YOU MUST PROVIDE A PASSWORD FIRST => PASS <password>\n");
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\n");
	if (_size > 2 || (_size == 2 && !validNick(vec[1]))) throw std::invalid_argument(" 432 :Erroneous nickname\n");
	if (_client->GetNickName() == vec[1]) throw std::invalid_argument(" 433 :Nickname is already in use\n");
	_nickName = vec[1];
}

bool	Nick::validNick(const std::string& nick) const
{
	if (nick.size() > 1 && nick.size() <= 9)
	{
		if (isSpecialChar(nick[0]) || std::isalpha(nick[0]))
		{
			std::string::const_iterator i = nick.begin();
			i++;
			for (; i != nick.end(); ++i)
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
	_client->setNickName(_nickName);
	return strdup("SETUP NICK CORRECTLY!\n");
}
Nick::~Nick() {}