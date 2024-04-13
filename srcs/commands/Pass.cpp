#include "commands/Pass.hpp"
#include "server.hpp"

Pass::Pass(Client* client, const std::vector<std::string>& vec) : _client(client), _password((vec.size() > 1 || vec.size() > 2) ? vec[1] : "")
{
  if (_client->GetIsRegistered()) throw std::invalid_argument(" 462 :Unauthorized command (already registered)\n");
  if (_password.empty()) throw std::invalid_argument("462 :Password incorrect\n");
}

Pass::~Pass() {}

char* Pass::execute() const {
      if (_password != _client->getServerPassword()) return strdup("462 :Password incorrect\n");
      _client->Register();
      _client->setIsValidatePassword();
      return strdup("Correct Password. Now run NICK <nickname>\n");
}
