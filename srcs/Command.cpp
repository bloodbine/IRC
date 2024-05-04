#include "Command.hpp"
#include "utils.hpp"

Command::Command(const std::vector<std::string>& vec, Client *client) : _client(client), _vec(vec), 
																		_size(vec.size()), _cmdType(-1),
																		_stringToSend(""),
																		_nickName(""),
																		_userName(""),
																		_realName("")
{
	(void)_client;
	_cmdType = getCmdType(vec[0]);
	switch (_cmdType)
	{
	case PASS:
		handlePass();
		break;
	case NICK:
		handleNick();
		break;
	case USER:
		/* HANDLE USER */
		handleUser();
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
		ERR_INVALIDCOMMAND();
		break;
	}
}

Command::~Command() {}

void	Command::handlePass()
{
	if (_client->getIsValidatedPassword()) ERR_ALREADYREGISTRED();
	if (_size != 2 || _vec[1] != _client->getServerPassword()) ERR_PASSWDMISMATCH();
	_client->setIsValidatePassword();
	_stringToSend = "Password was setup successfully! Proceed with setting a Nickname";
}

void	Command::handleNick()
{
	if (_client->getIsValidatedPassword() == false) missingPass();
	if (_size <= 1) ERR_NONICKNAMEGIVEN();
	_nickName = _vec[1];
	if (_size > 2 || (_size == 2 && !validNick(_nickName))) ERR_ERRONEUSNICKNAME(_nickName);
	if (server::clientExists(_nickName)) ERR_ALREADYREGISTRED();
	_client->setNickName(_nickName);
	_stringToSend =  "NICK " + _nickName + "\r\n";
}

void	Command::handleUser()
{
	if (_client->getIsregistered()) ERR_ALREADYREGISTRED();
	if (_client->getNickName() == "") missingNick();
	if (_size < 5) ERR_NEEDMOREPARAMS("USER");
	if (isValidUser(_vec) == false) ERR_SYNTAXPROBLEM();
	if (server::clientExists(_vec[1])) ERR_ALREADYREGISTRED();
	else server::addClient(_client);
	if (_vec[4][0] == ':') _realName = _vec[4].substr(1);
	else _realName = _vec[4];
	for (size_t i = 5; i < _size; i++) 
			_realName += " " + _vec[i];
	_client->setUserName(_vec[1]);
	_client->setRealUserName(_realName);
	_client->setHostname(getClientHostname(_client->getFd()));
	_client->setIsregistered();
	_stringToSend = ":" + server::getHostname() + " 001 " + _client->getNickName() + " :Welcome to the Internet Relay Network " + _client->getIdenClient() + "\r\n";
	_stringToSend += ":" + server::getHostname() + " 002 " + _client->getNickName() + " :Your host is " + server::getHostname() + ", running version 1.0\r\n";
	_stringToSend += ":" + server::getHostname() + " 003 " + _client->getNickName() + " :This server was created " + server::getCreationTime() + "\r\n";
	_stringToSend += ":" + server::getHostname() + " 221 " + _client->getNickName() + " :0\r\n";
	_stringToSend += ":" + server::getHostname() + " 004 " + _client->getNickName() + " :" + server::getHostname() + " 1.0 oiws obtkmlvsn\r\n";

}

void	Command::printStringToSend() const
{
	std::cout << "stringToSend: " << _stringToSend << std::endl;
}