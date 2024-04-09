#include "commands/Pass.hpp"
#include "server.hpp"

Pass::Pass(const std::vector<std::string>& vec) : _password(vec.size() > 1 ? vec[1] : "") {}

Pass::~Pass() {}

char* Pass::execute(server& server, Client& client) const {
  (void)client;
  if (_password.empty()) {
    std::string tmp = ":You need to specify a password after PASS\n";
    char* out = new char[tmp.size() + 1];
    std::strcpy(out, tmp.c_str());
    return out;
  }

  if (server.getPass() == _password) 
  {
      std::string tmp = "Correct Password. Now run NICK <nickname>\n";
      client.setIsValidatePassword();
      char* out = new char[tmp.size() + 1];
      std::strcpy(out, tmp.c_str());
      return out;
  } 
  else 
  {
      std::string tmp = "Wrong Password\n";
      char* out = new char[tmp.size() + 1];
      std::strcpy(out, tmp.c_str());
      return out;
  }
}

