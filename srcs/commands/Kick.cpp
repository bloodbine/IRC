#include "commands/Kick.hpp"
#include "server.hpp"

Kick::Kick(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _channel(""), _nick(""), _reasson("")
{
    // if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 3) ERR_NEEDMOREPARAMS("KICK");
    // More than 3 char throw invalid SYNTAX ERROR.

	// Check if valid _channel name
	if (isInvalidChannelName(vec[1])) ERR_NOSUCHCHANNEL();
	_channel = vec[1];

	// Check if is valid nick name
	if (validNick(vec[2]) == false) ERR_ERRONEUSNICKNAME(vec[2]);
	_nick = vec[2];

	// Read reasson
	if (_size >= 4)
	{
		if (vec[3][0] == ':') _reasson = vec[3].substr(1);
		else _reasson = vec[3];
		for (size_t i = 4; i < _size; i++) _reasson += " " + vec[i];
	}
}

char* Kick::execute() const
{
	std::string	out = "";
	std::cout << "THX FOR CALLINNG Kick\n";
	std::cout << "Reasson: " << _reasson << std::endl;
    //check if the channel is exist
	// std::cout << "> target is a user\n";
	
    return strdup(out.c_str());
}

Kick::~Kick()
{}

