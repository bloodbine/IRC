#include "commands/Quit.hpp"
#include "server.hpp"

Mode::Mode(Client* client, const std::vector<std::string>& vec) : _client(client), _size(vec.size()), _nickname(""), _mode("")
{
	(void)_client;
	if (_size != 3) ERR_NEEDMOREPARAMS("MODE");
	if (validNick(vec[1]) == false) ERR_ERRONEUSNICKNAME(vec[1]);
	_nickname = vec[1];

	// Verify that mode is valid mode
	if (isValidMode(vec[2]) == false) // ERR_UMODEUNKNOWNFLAG
	_mode = vec[2];
}

char* Mode::execute() const
{
	std::string	out = "";
	std::cout << "THX FOR CALLINNG Mode\n";
    //check if the channel is exist
	// std::cout << "> target is a user\n";
	
    return strdup(out.c_str());
}

Mode::~Mode()
{}