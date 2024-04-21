#include "commands/Notice.hpp"

Notice::Notice(Client* client, const std::vector<std:: string>& vec): _client(client), _size(vec.size())
{   
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    // if (vec[1] == "*")
    //     return ;
}

char* Notice::execute() const
{
    return (strdup(""));
}

Notice::~Notice()
{

}