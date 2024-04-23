#include "commands/Invite.hpp"
#include "server.hpp"

Invite::Invite(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _channel(""), _nick("")
{
    if (!_client->GetIsRegistered()) ERR_NOTREGISTERED();
    if (_size < 3) ERR_NEEDMOREPARAMS("INVITE");
    // More than 3 char throw invalid SYNTAX ERROR.
	if (_size != 3) ERR_SYNTAXPROBLEM();

	// Check if is valid nick name
	_nick = vec[1];

	// Check if valid _channel name
	if (isInvalidChannelName(vec[2])) ERR_NOSUCHCHANNEL();
	_channel = vec[2];
}

char* Invite::execute() const
{
	std::string	out = "";
	std::cout << "THX FOR CALLINNG INVITE\n";
    //check if the channel is exist
	// std::cout << "> target is a user\n";
	
    return strdup(out.c_str());
}

Invite::~Invite()
{}

