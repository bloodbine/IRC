#include "commands/Kick.hpp"
#include "server.hpp"

Kick::Kick(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _channel(""), _nick(""), _reason("")
{
	(void)_client;
	// int 
    // if (!_client->getIsregistered()) ERR_NOTREGISTERED();
    if (_size < 3) ERR_NEEDMOREPARAMS("KICK");
    // More than 3 char throw invalid SYNTAX ERROR.

	// Check if valid _channel name
	if (isInvalidChannelName(vec[1])) ERR_NOSUCHCHANNEL();
	_channel = vec[1];

	// Check if is valid nick name
	if (validNick(vec[2]) == false) ERR_ERRONEUSNICKNAME(vec[2]);
	_nick = vec[2];

	// check if fd is the same with the userFd
	// if ()

	// Read reasson
	if (_size >= 4)
	{
		if (vec[3][0] == ':') _reason = vec[3].substr(1);
		else _reason = vec[3];
		for (size_t i = 4; i < _size; i++) _reason += " " + vec[i];
	}
	else _reason = "it's the wish of the channel operator";
}

std::string Kick::execute() const
{
	if (server::channelExists(_channel) == false) ERR_NOSUCHCHANNEL();
	Channel *channel = server::getChannelByName(_channel);
	if (channel->getIsMember(_nick) == false) ERR_USERNOTINCHANNEL(_channel, _nick);
	if (_nick == _client->getNickName()) ERR_CANTKICKYOURSELF();
	if (channel->getIsOperator(_nick) == false) ERR_CHANOPRIVSNEEDED(_nick);
	// std::cout << "get operator : " << channel->getIsOperator(_nick) << std::endl;
	Client* client = server::getClientByFd(server::getClientFdByName(_nick));
	std::string	out = ":" + client->getIdenClient() + " leaves the channel " + _channel + \
		" because " + _reason + "\r\n";
	channel->removeUser(*client);
	return out;
}

Kick::~Kick()
{}

