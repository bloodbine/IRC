#include "commands/Pass.hpp"

#include "server.hpp"

Pass::Pass(const std::vector<std::string>& vec) : _password(vec.size() > 1 ? vec[1] : "") {}

Pass::~Pass() {}

char* Pass::execute(server& Server) const {
  if (_password.empty()) {
    std::string tmp = ":You need to specify a password after PASS\n";
    char* out = new char[tmp.size() + 1];
    std::strcpy(out, tmp.c_str());
    return out;
  }

  if (Server.getPass() == _password) 
  {
      std::string tmp = "true\n";
      char* out = new char[tmp.size() + 1];
      std::strcpy(out, tmp.c_str());
      return out;
  } 
  else 
  {
      std::string tmp = "false\n";
      char* out = new char[tmp.size() + 1];
      std::strcpy(out, tmp.c_str());
      return out;
  }
}

