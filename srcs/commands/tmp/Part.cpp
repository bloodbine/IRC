#include "commands/Part.hpp"
#include "server.hpp"

Part::Part(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _reasson("no reason was specified.")
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	_channelName = vec[1]; // extract channel name in index 1
	if (server::channelExists(_channelName) == false) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
	{
		_reasson = vec[2];
		for (size_t i = 3 ; i < _size; i++) _reasson += " " + vec[i];
	}
}

std::string Part::execute() const
{
	//check if the channel is exist
	 if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
	// check if channel as user
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
	std::string out = ":" + _client->getIdenClient() + " PART " + _channelName + " :" + _reasson + "\r\n";
	std::map<std::string, Client*> memberList = channel->getMemberList();
	std::map<std::string, Client*>::iterator start = memberList.begin();
	std::map<std::string, Client*>::iterator end = memberList.end();
	for (; start != end; start++)
			send((*start).second->getFd(), out.c_str(), out.length(), 0);
	if (channel->getIsOperator(_client->getNickName()))
		channel->removeOperator(*_client);
	channel->removeUser(*_client);
	if (channel->getClientList().size() == 0)
		server::removeChannel(channel->getName());
	return "";
}

Part::~Part()
{}

