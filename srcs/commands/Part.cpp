#include "commands/Part.hpp"
#include "server.hpp"

Part::Part(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size())
{
    server* srv = nullptr;
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("USER");
    
    const std::string& channelName = vec[1]; // extract channel name in index 1
    //check if the channel is exist
    if (!server::channelExists(channelName))  ERR_NOSUCHCHANNEL();
    // check if channel as user
    Channel* channel = srv->getChannelByName(channelName);
    if (!channel->hasUser(*client)) ERR_NOTONCHANNEL();
}

char* Part::execute() const
{
    return strdup("Bye bye \n");
}

Part::~Part()
{}

