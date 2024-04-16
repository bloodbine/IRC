#include "commands/Join.hpp"
#include "server.hpp"

Join::Join(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size())
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("JOIN");
    _channelName = vec[1]; // extract channel name in index 1
    if (isInvalidChannelName(_channelName)) ERR_NOSUCHCHANNEL();
    // Check if the _channelName is valid channel name
}

char* Join::execute() const
{
    std::string out = "";
    std::cout << ":" << _client->GetIdenClient() << " Join " << _channelName << std::endl;
    //check if the channel is exist
     if (!server::channelExists(_channelName)) server::addChannel(new Channel(_channelName, "Default topic", "Default mode"));
    // check if channel as user
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel->hasUser(*_client)) channel->addMember(_client);
    out += ":server.example.com 332" + _client->GetNickName() + " " + _channelName + ": " + channel->getTopic();
    std::cout << "SEND TO CLIENT \"e" << out << "\"" << std::endl;
	return strdup(out.c_str());
}

Join::~Join()
{}

