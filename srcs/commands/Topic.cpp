#include "commands/Topic.hpp"
#include "server.hpp"

Topic::Topic(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _topic(""), _clearTopic(false)
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size <= 1) ERR_NEEDMOREPARAMS("TOPIC");
	_channelName = vec[1];
	if (_size >= 3 && vec[2][0] == ':')
	{
		if (vec[2].size() == 1)
		{
			_clearTopic = true;
			return ;
		}
		if (vec[2][0] == ':') _topic += vec[2].substr(1);
		else _topic += vec[2];
		for (size_t i = 3; i < vec.size(); i++) _topic += " " + vec[i];
	}

}

std::string Topic::execute() const
{
	std::string	out;
	std::cout << ":" << _client->getIdenClient() << " Channel " << _channelName << std::endl;
	std::cout << ":" << _client->getIdenClient() << " Topic " << _topic << std::endl;
	std::cout << ":" << _client->getIdenClient() << " clearTopic " << _clearTopic << std::endl;
	//check if the channel is exist
	 if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
	// check if channel as user
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
	if (channel->getTopic() == "" && _topic == "")
		out = " 331 " + _channelName + " :No topic is set" + "\r\n";
	else if (_topic == "")
		out = " 332 " + _channelName + " :" + channel->getTopic() + "\r\n";
	else if (channel->getTopicRestrictFlag() == false || channel->getIsOperator(_client->getNickName()) == true)
	{
		channel->setTopic(_topic);
		out = " 332 " + _channelName + " :" + channel->getTopic() + "\r\n";
	}
	else
		ERR_CHANOPRIVSNEEDED(_channelName);
	std::cout << out;
	return out;
}

Topic::~Topic()
{}

