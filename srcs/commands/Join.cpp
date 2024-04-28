#include "commands/Join.hpp"
#include "server.hpp"

Join::Join(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _chanKey("")
{
	if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
	if (_size <= 1) ERR_NEEDMOREPARAMS("JOIN");
	_channelName = vec[1]; // extract channel name in index 1
	if (isInvalidChannelName(_channelName)) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
		_chanKey = vec[2];
	// Check if the _channelName is valid channel name
}

char* Join::execute() const
{
	std::string out = "";
	std::cout << ":" << _client->GetIdenClient() << " Join " << _channelName << std::endl;
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
			if (channel->getInvitedList().find(_client->GetNickName()) == channel->getInvitedList().end())
				ERR_INVITEONLYCHAN(_channelName);
			else
				channel->getInvitedList().erase(_client->GetNickName());
		}
		if (channel->getUserLimit() != 0 && channel->getUserLimit() == static_cast<int>(channel->getClientList().size()))
			ERR_CHANNELISFULL(_channelName);
		channel->addMember(_client);
	}
	else
		ERR_USERONCHANNEL(_channelName);
	_client->addChannelToChannelList(channel);
	_client->incrementTotalChannels();
	out += ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@" + server::getServerIp() +" JOIN " + _channelName + "\r\n";
	out += ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@" + server::getServerIp() +" 331 " + _client->GetNickName() + " " + _channelName + " :No topic is set\r\n";
	out += ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@" + server::getServerIp() +" 353 " + _client->GetNickName() + " = " + _channelName + " :" + channel->getClientList() + "\r\n";
	out += ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@" + server::getServerIp() +" 366 " + _client->GetNickName() + " " + _channelName + " :End of /NAMES list.\r\n";

	std::cout << "SEND TO CLIENT \"" << out << "\"" << std::endl;
	return strdup(out.c_str());
}

Join::~Join()
{}
