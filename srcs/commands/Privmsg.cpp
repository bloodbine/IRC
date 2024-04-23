#include "commands/Privmsg.hpp"
#include "server.hpp"

Privmsg::Privmsg(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _msg(""), _target(""), _targetIsChannel(false) 
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 3) ERR_NEEDMOREPARAMS("PRIVMSG");
	if (vec[1][0] == '#')
	{
		if (isInvalidChannelName(vec[1]) == false) ERR_NOSUCHCHANNEL();
		_targetIsChannel = true;
	}
	else if (validNick(vec[1]) == false) ERR_ERRONEUSNICKNAME(vec[1]);
	_target = vec[1];
	_msg += vec[2];
	for (size_t i = 3 ; i < _size; i++) _msg += " " + vec[i];
}

char* Privmsg::execute() const
{
	std::string	out = "";
    //check if the channel is exist
    if (_targetIsChannel) std::cout << "> target is channel\n";
    else
	{
		// std::cout << "> target is a user\n";
		if (server::clientExists(_target) == false) ERR_NOSUCHNICK(_target);
		else std::cout << "Client: " << _target << " actually exists\n";
		out = ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@127.0.0.1 PRIVMSG " + _target + " " + _msg + "\r\n";
		std::cout << out << std::endl;
	}
	// std::cout << "Message to " << _target << std::endl;
	std::cout << _msg << std::endl;
    return strdup(out.c_str());
}

Privmsg::~Privmsg()
{}

