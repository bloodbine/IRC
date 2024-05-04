#include "commands/Quit.hpp"
#include "server.hpp"

Quit::Quit(Client* client, const std::vector<std::string>& vec): _client(client), _size(vec.size()), _reasson("")
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();

	// Read reasson
	if (_size > 1)
	{
		_reasson += vec[1].substr(1);
		for (size_t i = 2; i < _size; i++) _reasson += " " + vec[i];
	}
}

std::string Quit::execute() const
{
	std::string	out = "";
	std::cout << "THX FOR CALLINNG Quit\r\n";
	std::cout << "Reasson: " << _reasson << std::endl;
	
	return out;
}

Quit::~Quit()
{}

