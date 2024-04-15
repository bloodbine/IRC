#include "commands/Part.hpp"
#include "server.hpp"

Part::Part(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size())
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("USER");
    
    _channelName = vec[1]; // extract channel name in index 1
    //check if the channel is exist
}

char* Part::execute() const
{
    std::cout << ":" << _client->GetIdenClient() << " PART " << _channelName << std::endl;
     if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
    // check if channel as user
    Channel* channel = server::getChannelByName(_channelName);
    if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
    channel->removeUser(*_client);
    return strdup("Bye Bye \n");
}

Part::~Part()
{}

