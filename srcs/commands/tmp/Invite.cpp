#include "commands/Invite.hpp"
#include "server.hpp"

Invite::Invite(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _channel(""), _nick("")
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size < 3) ERR_NEEDMOREPARAMS("INVITE");
	// More than 3 char throw invalid SYNTAX ERROR.
	if (_size != 3) ERR_SYNTAXPROBLEM();

	// Check if is valid nick name
	if (validNick(vec[1]) == false) ERR_ERRONEUSNICKNAME(vec[1]);
	_nick = vec[1];
	if (server::clientExists(_nick) == false) ERR_NOSUCHNICK(_nick);

	// Check if valid _channel name
	if (isInvalidChannelName(vec[2]) == true) ERR_NOSUCHCHANNEL();
	_channel = vec[2];
}

std::string Invite::execute() const
{
	std::string	out = "";
	if (server::channelExists(_channel))
	{
		Channel* channel = server::getChannelByName(_channel);
		if (channel->getInviteFlag() == 1)
		{
			if (channel->getIsOperator(_client->getNickName()) == true)
				channel->addInvited(server::getClientByFd(server::getClientFdByName(_nick)));
			else if (channel->getIsMember(_client->getNickName()) == true)
				ERR_CHANOPRIVSNEEDED(_channel);
		}
		else if (channel->getIsMember(_nick) == true)
			ERR_USERONCHANNEL(_channel);
	}
	out.append(":" + _client->getIdenClient()+ " 341 : INVITE " + _nick + " " + _channel + "\r\n");
	Client* target = server::getClientByFd(server::getClientFdByName(_nick));
	send(target->getFd(), out.c_str(), out.length(), 0);
	return out;
}

Invite::~Invite() {}