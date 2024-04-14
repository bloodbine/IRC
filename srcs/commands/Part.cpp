#include "commands/Part.hpp"
#include "server.hpp"

Part::Part(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size())
{
    server& server;
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("USER");
    
    const std::string& channelName = vec[1]; // extract channel name in index 1
    //check if the channel is exist
    if ( channelExists(channelName) )
    {
        // remove client from channel member list
        //Brodcast PART message to other channel member;
    }
    else{
        // case where the channel doesn't exist;
    }
}

char* Part::execute() const
{

    return strdup("Bye bye \n");
}

Part::~Part()
{
}
