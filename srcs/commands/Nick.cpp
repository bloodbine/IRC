#include "commands/Nick.hpp"
#include "server.hpp"

Nick::Nick(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size())
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) throw std::invalid_argument(" 431 :No nickname given\n");
	_nickName = vec[1];
	if (_size > 2 || (_size == 2 && !validNick())) throw std::invalid_argument(" 432 :Erroneous nickname\n");
	if (_client->GetNickName() == vec[1]) throw std::invalid_argument(" 433 :Nickname is already in use\n");
	_nickName = vec[1];
}

bool	Nick::validNick() const
{
	if (_nickName.size() > 1 && _nickName.size() <= 9)
	{
		if (isSpecialChar(_nickName[0]) || std::isalpha(_nickName[0]))
		{
			std::string::const_iterator i = _nickName.begin();
			i++;
			for (; i != _nickName.end(); ++i)
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
	if (validNick()) _client->setNickName(_nickName);
	else throw std::invalid_argument(" 432 :Erroneous nickname\n");
	std::string	out = "NICK " + _nickName + "\n";
	return strdup(out.c_str());
}
Nick::~Nick() {}