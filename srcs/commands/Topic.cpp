#include "commands/Topic.hpp"
#include "server.hpp"

Topic::Topic(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _topic(""), _clearTopic(false)
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 1) ERR_NEEDMOREPARAMS("TOPIC");
	_channelName = vec[1];
	if (_size >= 3 && vec[2][0] == ':')
	{
		if (vec[2].size() == 1)
		{
			_clearTopic = true;
			return ;
		}
		_topic += vec[2].substr(1);
		for (size_t i = 3; i < vec.size(); i++) _topic += " " + vec[i];
	}

}

void Topic::execute()
{
	std::string	out;
    std::cout << ":" << _client->GetIdenClient() << " Channel " << _channelName << std::endl;
    std::cout << ":" << _client->GetIdenClient() << " Topic " << _topic << std::endl;
    std::cout << ":" << _client->GetIdenClient() << " clearTopic " << _clearTopic << std::endl;
    //check if the channel is exist
     if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
    // check if channel as user
    Channel* channel = server::getChannelByName(_channelName);
    if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
	if (_topic == "") out = " 331 RPL_NOTOPIC " + _channelName + " :No topic is set\n";
	else
	{
		channel->setTopic(_topic);
		out = " 332 RPL_TOPIC " + _channelName + " :" + _topic + "\n";
	}
    _out = strdup(out.c_str());
}

int Topic::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}

Topic::~Topic()
{}

