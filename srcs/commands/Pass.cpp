#include "commands/Pass.hpp"
#include "server.hpp"

Pass::Pass(Client* client, const std::vector<std::string>& vec) : _client(client), _password((vec.size() > 1 || vec.size() > 2) ? vec[1] : "")
{
  if (_client->getIsValidatedPassword()) ERR_ALREADYREGISTRED();
  if (_password.empty()) throw std::invalid_argument("462 :Password incorrect\n");
}

void Pass::execute() {
      if (_password != _client->getServerPassword())
      {
        std::string out = "462 :Password incorrect\n";
        _out = strdup(out.c_str());
      }
      // _client->Register();
      std::string out = "Correct Password. Now run NICK <nickname>\n";
      _client->setIsValidatePassword();
      _out = strdup(out.c_str());
}

int Pass::sendToClient() const
{
	int	fdToSend = _client->getFd();
	return (send(fdToSend, _out, std::strlen(_out), 0));
}


Pass::~Pass() {}
