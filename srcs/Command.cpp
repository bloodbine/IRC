#include "Command.hpp"
#include "utils.hpp"

Command::Command(const std::vector<std::string>& vec, Client *client) : _client(client), _vec(vec), 
																		_size(vec.size()), _cmdType(-1),
																		_stringToSend(""),
																		_nickName(""),
																		_userName(""),
																		_realName(""),
																		_channelName(""),
																		_chanKey(""),
																		_reasson("no reason was specified."),
																		_serverName(""),
																		_topic(""),
																		_clearTopic(false)
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
		break;
	case PART:
		handlePart();
		break;
	case JOIN:
		handleJoin();
		break;
	case PING:
		/* HANDLE PING */
		handlePing();
		break;
	case NOTICE:
		/* HANDLE NOTICE */
		handleNotice();
		break;
	case TOPIC:
		/* HANDLE TOPIC */
		handleTopic();
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
	_stringToSend = "Password was setup successfully! Proceed with setting a Nickname\n";
	// MISSING TO CHECK IF IT FAILS TO SEND
	selfClientSend(_stringToSend, _client->getFd());
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
	// MISSING TO CHECK IF IT FAILS TO SEND
	selfClientSend(_stringToSend, _client->getFd());
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
	// MISSING TO CHECK IF IT FAILS TO SEND
	selfClientSend(_stringToSend, _client->getFd());

}

void	Command::handleJoin()
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size <= 1) ERR_NEEDMOREPARAMS("JOIN");
	_channelName = _vec[1];
	if (isInvalidChannelName(_channelName)) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
		_chanKey = _vec[2];
	if (!server::channelExists(_channelName))
	{
		if (_client->getTotalChannels() >= 4) ERR_TOOMANYCHANNELS(_channelName);
		server::addChannel(new Channel(_channelName));
		server::getChannelByName(_channelName)->addOperator(_client);
	}
	Channel* channel = server::getChannelByName(_channelName);
	// Add protection
	if (!channel) ERR_NOSUCHCHANNEL();
	if (!channel->hasUser(*_client))
	{
		if (_client->getTotalChannels() >= 4) ERR_TOOMANYCHANNELS(_channelName);
		if (channel->getChanKey() != "")
		{
			if (_chanKey == "") ERR_BADCHANNELKEY(_channelName, "No key given");
			else if (_chanKey != channel->getChanKey()) ERR_BADCHANNELKEY(_channelName, ": Cannot join channel (+k)");
		}
		if (channel->getInviteFlag() == 1)
		{
			if (channel->getInvitedList().find(_client->getNickName()) == channel->getInvitedList().end())
				ERR_INVITEONLYCHAN(_channelName);
			else
				channel->getInvitedList().erase(_client->getNickName());
		}
		if (channel->getUserLimit() != 0 && channel->getUserLimit() == static_cast<int>(channel->getClientList().size()))
			ERR_CHANNELISFULL(_channelName);
		channel->addMember(_client);
	}
	else
		ERR_USERONCHANNEL(_channelName);
	_client->addChannelToChannelList(channel);
	_client->incrementTotalChannels();
	_stringToSend += ":" + _client->getIdenClient() +" JOIN " + _channelName + "\r\n";
	if (channel->getTopic() == "")
		_stringToSend += ":" + _client->getIdenClient() +" 331 " + _client->getNickName() + " " + _channelName + " :No topic is set\r\n";
	else
		_stringToSend += ":" + _client->getIdenClient() +" 331 " + _client->getNickName() + " " + _channelName + " :" + channel->getTopic() + "\r\n";
	_stringToSend += ":" + _client->getIdenClient() +" 353 " + _client->getNickName() + " = " + _channelName + " :" + channel->getClientList() + "\r\n";
	_stringToSend += ":" + _client->getIdenClient() +" 366 " + _client->getNickName() + " " + _channelName + " :End of /NAMES list.\r\n";
	// check if it fails and handle it
	if (sendToChannel(_stringToSend, _channelName) < 0) std::cout << "failed to send" << std::endl;
}

void	Command::handlePart()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	_channelName = _vec[1]; // extract channel name in index 1
	if (server::channelExists(_channelName) == false) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
	{
		_reasson = _vec[2];
		for (size_t i = 3 ; i < _size; i++) _reasson += " " + _vec[i];
	}
	Channel* channel = server::getChannelByName(_channelName);
	if (!channel) ERR_NOTONCHANNEL();
	if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
	_stringToSend = ":" + _client->getIdenClient() + " PART " + _channelName + " :" + _reasson + "\r\n";
	if (sendToChannel(_stringToSend, _channelName) < 0) std::cout << "failed to send" << std::endl;
	if (channel->getIsOperator(_client->getNickName()))
		channel->removeOperator(*_client);
	channel->removeUser(*_client);
	if (channel->getClientList().size() == 0)
		server::removeChannel(channel->getName());
}


void	Command::printStringToSend() const
{
	std::cout << "stringToSend: " << _stringToSend << std::endl;
}

void	Command::handlePing()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	if (_size == 1) ERR_NOORIGIN();
	if ( _size == 2) _serverName = _vec[1];
	else
	{
		for (unsigned i = 2; i < _size; ++i)
		{
			if (i != _size - 1)
				_serverName += _vec[i] + " ";
			else
				_serverName += _vec[i];
		}
	}
	_stringToSend = "PONG " + _client->getNickName() + " " + _serverName + "\r\n";
	selfClientSend(_stringToSend, _client->getFd());
}

void	Command::handleNotice()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	_stringToSend = "";
	// check if it fails and handle it
	if (selfClientSend(_stringToSend, _client->getFd()) < 0) std::cout << "failed to send" << std::endl;
}

void	Command::handleTopic()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	if (_size <= 1) ERR_NEEDMOREPARAMS("TOPIC");
	_channelName = _vec[1];
	if (_size >= 3 && _vec[2][0] == ':')
	{
		if (_vec[2].size() == 1)
		{
			_clearTopic = true;
			return ;
		}
		if (_vec[2][0] == ':') _topic += _vec[2].substr(1);
		else _topic += _vec[2];
		for(size_t i = 3; i < _size; i++) _topic += " " + _vec[i];
	}

	std::cout << ":" << _client->getIdenClient() << " Channel " << _channelName << std::endl;
	std::cout << ":" << _client->getIdenClient() << " Topic " << _topic << std::endl;
	std::cout << ":" << _client->getIdenClient() << " clearTopic " << _clearTopic << std::endl;

	//Heck if the Channel exist
	if (!server::channelExists(_channelName)) ERR_NOSUCHCHANNEL();
	//HECK if Channel has User
	Channel* channel = server::getChannelByName(_channelName);
	// Add protection
	if (!channel) ERR_NOSUCHCHANNEL();
	if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
	if (channel->getTopic() == "" && _topic == "")
		_stringToSend = " 331 " + _channelName + " :No topic is set" + "\r\n";
	else if (_topic == "")
		_stringToSend = " 332 " + _channelName + " :" + channel->getTopic() + "\r\n";
	else if (channel->getTopicRestrictFlag() == false || channel->getIsOperator(_client->getNickName()) == true)
	{
		channel->setTopic(_topic);
		_stringToSend = " 332 " + _channelName + " :" + channel->getTopic() + "\r\n";
	}
	else
		ERR_CHANOPRIVSNEEDED(_channelName);
	// check if it fails and handle it
	if (sendToChannel(_stringToSend, _channelName) < 0) std::cout << "failed to send" << std::endl;
}