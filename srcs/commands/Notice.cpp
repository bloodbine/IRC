#include "commands/Notice.hpp"

Notice::Notice(Client* client, const std::vector<std:: string>& vec): _client(client), _size(vec.size())
{   
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    // if (vec[1] == "*")
    //     return ;
}

void Notice::execute()
{
    std::string out = "";
    _out = strdup(out.c_str());
}

int Notice::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}

Notice::~Notice()
{

}