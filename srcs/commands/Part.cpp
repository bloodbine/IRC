#include "commands/Part.hpp"
#include "server.hpp"

Part::Part(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size())
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("USER");
    _channelName = vec[1]; // extract channel name in index 1

}

void Part::execute()
{
    std::cout << ":" << _client->GetIdenClient() << " PART " << _channelName << std::endl;
    //check if the channel is exist
     if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
    // check if channel as user
    Channel* channel = server::getChannelByName(_channelName);
    if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
    channel->removeUser(*_client);
    std::string out = "Bye Bye \n";
    _out = strdup(out.c_str());
}

int Part::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}


Part::~Part()
{}

