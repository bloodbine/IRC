#include "commands/Pass.hpp"
#include "server.hpp"

Pass::Pass(Client* client, const std::vector<std::string>& vec) : _client(client), _password((vec.size() > 1 || vec.size() > 2) ? vec[1] : "")
{
  if (_client->getIsValidatedPassword()) ERR_ALREADYREGISTRED();

  if (vec.size() != 2) throw std::invalid_argument("462 :Password incorrect\r\n");
}

Pass::~Pass() {}

std::string Pass::execute() const {
      if (_password != _client->getServerPassword()) return "462 :Password incorrect\r\n";
      // _client->registerClient();
      _client->setIsValidatePassword();
      return "";
}
