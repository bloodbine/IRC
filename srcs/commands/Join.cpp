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

void Join::execute()
{
    std::string out = "";
    std::cout << ":" << _client->GetIdenClient() << " Join " << _channelName << std::endl;
    //check if the channel is exist
     if (!server::channelExists(_channelName)) server::addChannel(new Channel(_channelName, "Default topic", "Default mode"));
    // check if channel as user
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel->hasUser(*_client)) channel->addMember(_client);
    out += " 332 " + _client->GetNickName() + " " + _channelName + ": " + channel->getTopic() + "\n";
    out += " 353 " + _client->GetNickName() + " " + _channelName + ": " + channel->getClientList() + "\n";
    out += " 366 " + _client->GetNickName() + " " + _channelName + ": End of /NAMES list.\n";

    std::cout << "SEND TO CLIENT \"" << out << "\"" << std::endl;
    _out = strdup(out.c_str());
}

int Join::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}


Join::~Join()
{}

