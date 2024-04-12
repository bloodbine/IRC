#include "commands/Pass.hpp"
#include "server.hpp"

Pass::Pass(const std::vector<std::string>& vec) : _password(vec.size() > 1 ? vec[1] : "") {}

Pass::~Pass() {}

std::string Pass::errorMessage(int errorCode) const {
    switch (errorCode) {
        case ERR_ALREADYREGISTRED:
            return " 462 :Unauthorized command (already registered)\n";
        case ERR_PASSWDMISMATCH:
            return " 464 :Password incorrect\n";
        default:
            return ""; // Default case, no error message
    }
}

char* Pass::execute(server& server, Client& client) const {
    if (client.GetIsRegistered()) {
        return strdup(errorMessage(ERR_ALREADYREGISTRED).c_str());
    } else if (_password.empty()) {
        return strdup(":You need to specify a password after PASS\n");
    } else {
        if (server.getPass() == _password && !client.GetIsRegistered()) {
            client.Register();
            client.setIsValidatePassword();
            return strdup("Correct Password. Now run NICK <nickname>\n");
        } else {
            return strdup(errorMessage(ERR_PASSWDMISMATCH).c_str());
        }
    }
}
