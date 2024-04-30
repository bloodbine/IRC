#include "commands/Privmsg.hpp"
#include "server.hpp"

Privmsg::Privmsg(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _msg(""), _target(""), _targetIsChannel(false) 
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size < 3) ERR_NEEDMOREPARAMS("PRIVMSG");
	if (vec[1][0] == '#')
	{
		if (isInvalidChannelName(vec[1])) ERR_NOSUCHCHANNEL();
		_targetIsChannel = true;
	}
	else if (validNick(vec[1]) == false) ERR_ERRONEUSNICKNAME(vec[1]);
	_target = vec[1];
	_msg += vec[2];
	if (_msg[0] == ':') _msg.erase(_msg.begin());
	for (size_t i = 3 ; i < _size; i++) _msg += " " + vec[i];
}

std::string Privmsg::execute() const
{
	std::string	out = "";
	//check if the channel is exist
	if (_targetIsChannel) std::cout << ">>> channel " << _target << " exists: " << server::channelExists(_target) << std::endl;
	else std::cout << ">>> client " << _target << " exists: " << server::clientExists(_target) << std::endl;
	if (_targetIsChannel && server::channelExists(_target) == false) ERR_NOSUCHCHANNEL();
	else if (!_targetIsChannel && server::clientExists(_target) == false) ERR_NOSUCHNICK(_target);
	out = ":" + _client->getIdenClient() + " PRIVMSG " + _target + " :" + _msg + "\r\n";
	Channel* channel = server::getChannelByName(_target);
	std::map<std::string, Client*> memberList = channel->getMemberList();
	std::map<std::string, Client*>::iterator start = memberList.begin();
	std::map<std::string, Client*>::iterator end = memberList.end();
	for (; start != end; start++)
	{
		if ((*start).second != _client)
			send((*start).second->getFd(), out.c_str(), out.length(), 0);
	}
	return "";
}

Privmsg::~Privmsg() {}

