#include "commands/Notice.hpp"

Notice::Notice(Client* client, const std::vector<std:: string>& vec): _client(client), _size(vec.size())
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
}

std::string Notice::execute() const
{
	return ("");
}

Notice::~Notice()
{

}