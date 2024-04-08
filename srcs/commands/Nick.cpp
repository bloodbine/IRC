#include "commands/Nick.hpp"
#include "server.hpp"

char* Nick::ERR_NONICKNAMEGIVEN(const std::string& serverIp) const
{
	std::string tmp = serverIp;
	tmp += "\t431 ::No nickname given\n";
	char	*out = new char[tmp.size() + 1];
	std::strcpy(out, tmp.c_str());
	return (out);
}
//            ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
//            ERR_UNAVAILRESOURCE             ERR_RESTRICTED

Nick::Nick(const std::vector<std::string>& vec) : _size(vec.size()) {}

char*	Nick::execute(server& Server) const
{
	char	*out;
	if (_size == 1) out = ERR_NONICKNAMEGIVEN(Server.getServerIp());
	else {
		std::string tmp = "Hello Nick!\n";
		out = new char[tmp.size() + 1];
		std::strcpy(out, tmp.c_str());
	}
	return out;
}
Nick::~Nick() {}