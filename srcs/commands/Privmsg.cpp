#include "commands/Privmsg.hpp"
#include "server.hpp"

Privmsg::Privmsg(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _msg(""), _target(""), _targetIsChannel(false)
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 3) ERR_NEEDMOREPARAMS("PRIVMSG");
	_target = vec[1];
	if (vec[1][0] == '#') _targetIsChannel = true;
	_msg += vec[2];
	for (size_t i = 3 ; i < _size; i++) _msg += " " + vec[i];
}

void Privmsg::execute()
{
	std::string	out = "";
    //check if the channel is exist
    if (_targetIsChannel) std::cout << "> target is channel\n";
    else
	{
		// std::cout << "> target is a user\n";
		out = ":" + _client->GetNickName() + "!" + _client->GetUserName() + "@127.0.0.1 PRIVMSG " + _target + " " + _msg + "\r\n";
		std::cout << out << std::endl;
	}
	_out = strdup(out.c_str());
	// std::cout << "Message to " << _target << std::endl;
}

int Privmsg::sendToClient() const
{
	int	fdToSend = server::getClientFdByNickName(_target);
	if (fdToSend == -1) ERR_NOSUCHNICK(_target);

	return (send(fdToSend, _out, std::strlen(_out), 0));
}


Privmsg::~Privmsg()
{}

