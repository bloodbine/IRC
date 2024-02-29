#include "parser.hpp"

/*
Returns -1 when the first word of the text is not a valid CMD.
Otherwise returns the int value representing the CMD.
*/
int	isValidCmd(const std::string& text)
{
	std::stringstream	ss(text);
	std::string	cmd;

	ss >> cmd;

	if (cmd == "PRIVMSG") return PRIVMSG;
	if (cmd == "PASS") return PASS;
	if (cmd == "WHOIS") return WHOIS;
	if (cmd == "WHO") return WHO;
	if (cmd == "PING") return PING;
	if (cmd == "CAP") return CAP;
	if (cmd == "PART") return PART;
	if (cmd == "LIST") return LIST;
	if (cmd == "MODE") return MODE;
	if (cmd == "QUIT") return QUIT;
	if (cmd == "JOIN") return JOIN;
	if (cmd == "NICK") return NICK;
	if (cmd == "MOTD") return MOTD;
	if (cmd == "TOPIC") return TOPIC;
	return -1;
}
