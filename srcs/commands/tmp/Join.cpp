#include "commands/Join.hpp"
#include "server.hpp"

Join::Join(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _chanKey("")
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size <= 1) ERR_NEEDMOREPARAMS("JOIN");
	_channelName = vec[1]; // extract channel name in index 1
	if (isInvalidChannelName(_channelName)) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
		_chanKey = vec[2];
	// Check if the _channelName is valid channel name
}

std::string Join::execute() const
{
	std::string out = "";
	std::cout << ":" << _client->getIdenClient() << " Join " << _channelName << std::endl;
	//check if the channel is exist
	if (!server::channelExists(_channelName))
	{
		if (_client->getTotalChannels() >= 4) ERR_TOOMANYCHANNELS(_channelName);
		server::addChannel(new Channel(_channelName));
		server::getChannelByName(_channelName)->addOperator(_client);
	}
	// check if channel as user
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel->hasUser(*_client))
	{
		if (_client->getTotalChannels() >= 4) ERR_TOOMANYCHANNELS(_channelName);
		if (channel->getChanKey() != "")
		{
			if (_chanKey == "") ERR_BADCHANNELKEY(_channelName, "No key given");
			else if (_chanKey != channel->getChanKey()) ERR_BADCHANNELKEY(_channelName, ": Cannot join channel (+k)");
		}
		if (channel->getInviteFlag() == 1)
		{
			if (channel->getInvitedList().find(_client->getNickName()) == channel->getInvitedList().end())
				ERR_INVITEONLYCHAN(_channelName);
			else
				channel->getInvitedList().erase(_client->getNickName());
		}
		if (channel->getUserLimit() != 0 && channel->getUserLimit() == static_cast<int>(channel->getClientList().size()))
			ERR_CHANNELISFULL(_channelName);
		channel->addMember(_client);
	}
	else
		ERR_USERONCHANNEL(_channelName);
	_client->addChannelToChannelList(channel);
	_client->incrementTotalChannels();
	out += ":" + _client->getIdenClient() +" JOIN " + _channelName + "\r\n";
	if (channel->getTopic() == "")
		out += ":" + _client->getIdenClient() +" 331 " + _client->getNickName() + " " + _channelName + " :No topic is set\r\n";
	else
		out += ":" + _client->getIdenClient() +" 331 " + _client->getNickName() + " " + _channelName + " :" + channel->getTopic() + "\r\n";
	out += ":" + _client->getIdenClient() +" 353 " + _client->getNickName() + " = " + _channelName + " :" + channel->getClientList() + "\r\n";
	out += ":" + _client->getIdenClient() +" 366 " + _client->getNickName() + " " + _channelName + " :End of /NAMES list.\r\n";

	std::cout << "SEND TO CLIENT \"" << out << "\"" << std::endl;
	return out;
}

Join::~Join()
{}
