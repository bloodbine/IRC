#include "Command.hpp"
#include "utils.hpp"

Command::Command(const std::vector<std::string>& vec, Client *client) : _client(client), _cmdType(-1), _stringToSend("")
{
	(void)client;
	_cmdType = getCmdType(vec[0]);
	switch (_cmdType)
	{
	case PASS:
		/* HANDLE PASS */
		std::cout << "You called PASS\n";
		break;
	case NICK:
		/* HANDLE NICK */
		std::cout << "You called NICK\n";
		break;
	case USER:
		/* HANDLE USER */
		std::cout << "You called USER\n";
		break;
	case PART:
		/* HANDLE PART */
		std::cout << "You called PART\n";
		break;
	case JOIN:
		/* HANDLE JOIN */
		std::cout << "You called JOIN\n";
		break;
	case PING:
		/* HANDLE PING */
		std::cout << "You called PING\n";
		break;
	case NOTICE:
		/* HANDLE NOTICE */
		std::cout << "You called NOTICE\n";
		break;
	case TOPIC:
		/* HANDLE TOPIC */
		std::cout << "You called TOPIC\n";
		break;
	case PRIVMSG:
		/* HANDLE PRIVMSG */
		std::cout << "You called PRIVMSG\n";
		break;
	case INVITE:
		/* HANDLE INVITE */
		std::cout << "You called INVITE\n";
		break;
	case KICK:
		/* HANDLE KICK */
		std::cout << "You called KICK\n";
		break;
	case QUIT:
		/* HANDLE QUIT */
		std::cout << "You called QUIT\n";
		break;
	case MODE:
		/* HANDLE MODE */
		std::cout << "You called MODE\n";
		break;
	case SHUTDOWN:
		/* HANDLE SHUTDOWN */
		std::cout << "You called SHUTDOWN\n";
		break;
	default:
		break;
	}
}
Command::~Command() {}