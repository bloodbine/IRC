#include "Command.hpp"
#include "utils.hpp"

Command::Command(const std::vector<std::string>& vec, Client *client, int i) :	_client(client), _vec(vec), 
																				_size(vec.size()), _cmdType(-1),
																				_stringToSend(""),
																				_nickName(""),
																				_userName(""),
																				_realName(""),
																				_channelName(""),
																				_chanKey(""),
																				_reason("no reason was specified."),
																				_serverName(""),
																				_topic(""),
																				_msg(""),
																				_target(""),
																				_targetIsChannel(false),
																				_clearTopic(false),
																				_i(i),
																				_channelObj(NULL),
																				_mode(""),
																				_parameter("")
{
	if (!client) throw std::invalid_argument("You can't provide a NULL Client!");
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
			handleUser();
			break;
		case PART:
			handlePart();
			break;
		case JOIN:
			handleJoin();
			break;
		case PING:
			handlePing();
			break;
		case NOTICE:
			handleNotice();
			break;
		case TOPIC:
			handleTopic();
			break;
		case PRIVMSG:
			handlePrivmsg();
			break;
		case INVITE:
			handleInvite();
			break;
		case KICK:
			handleKick();
			break;
		case MODE:
			handleMode();
			break;
		case QUIT:
			handleQuit();
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
	// _stringToSend = "";
	// selfClientSend(_stringToSend, _client->getFd());
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
	sendToChannel(_stringToSend, _channelName);
}

void	Command::handlePart()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	_channelName = _vec[1]; // extract channel name in index 1
	if (server::channelExists(_channelName) == false) ERR_NOSUCHCHANNEL();
	if (_size >= 3)
	{
		_reason = _vec[2];
		for (size_t i = 3 ; i < _size; i++) _reason += " " + _vec[i];
	}
	Channel* channel = server::getChannelByName(_channelName);
	if (channel)
	{
		if (!channel) ERR_NOTONCHANNEL();
		if (!channel->hasUser(*_client)) ERR_NOTONCHANNEL();
		_stringToSend = ":" + _client->getIdenClient() + " PART " + _channelName + " :" + _reason + "\r\n";
		sendToChannel(_stringToSend, _channelName);
		if (channel->getIsOperator(_client->getNickName()))
			channel->removeOperator(*_client);
		channel->removeUser(*_client);
	}
	// should send stuff
	sendToChannel(_stringToSend, _channelName);
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
	selfClientSend(_stringToSend, _client->getFd());
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
	sendToChannel(_stringToSend, _channelName);
}

void	Command::handlePrivmsg()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	if (_size < 3) ERR_NEEDMOREPARAMS("PRIVMSG");
	_target = _vec[1];
	if (_target.find("#") != std::string::npos)
	{
		if (isInvalidChannelName(_vec[1])) ERR_NOSUCHCHANNEL();
		_targetIsChannel = true;
	}
	else if (validNick(_vec[1]) == false) ERR_ERRONEUSNICKNAME(_vec[1]);
	_msg += _vec[2];
	if (_msg[0] == ':') _msg.erase(_msg.begin());
	for (size_t i = 3; i < _size; i++) _msg += ' ' + _vec[i];
	//check if the channel is exist
	if (_targetIsChannel) std::cout << ">>> channel " << _target << " exists: " << server::channelExists(_target) << std::endl;
	else std::cout << ">>> client " << _target << " exists: " << server::clientExists(_target) << std::endl;
	if (_targetIsChannel && server::channelExists(_target) == false) ERR_NOSUCHCHANNEL();
	else if (!_targetIsChannel && server::clientExists(_target) == false) ERR_NOSUCHNICK(_target);
	_stringToSend = ":" + _client->getIdenClient() + " PRIVMSG " + _target + " :" + _msg + "\r\n";
	if (_targetIsChannel)
	{
		_channelName = _vec[1];
		Channel* channel = server::getChannelByName(_target);
			// Add protection
		if (!channel) ERR_NOSUCHCHANNEL();
		if (!channel->getIsMember(_client->getNickName())) ERR_CANNOTSENDTOCHAN(_channelName);
		sendToChannel(_stringToSend, _channelName);
	}
	else
	{
		Client* client = server::getClientByFd(server::getClientFdByName(_target));
		selfClientSend(_stringToSend, client->getFd());
	}
}

void	Command::handleInvite()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	if (_size < 3) ERR_NEEDMOREPARAMS("INVITE");
	// More than 3 char throw invalid SYNTAX ERROR.
	if (_size != 3) ERR_SYNTAXPROBLEM();
	// Check if is valid nick name
	if (validNick(_vec[1]) == false) ERR_ERRONEUSNICKNAME(_vec[1]);
	_nickName = _vec[1];
	if (server::clientExists(_nickName) == false) ERR_NOSUCHNICK(_nickName);
	// Check if valid _channel name
	if (isInvalidChannelName(_vec[2]) == true) ERR_NOSUCHCHANNEL();
	_channelName = _vec[2];
	if (server::channelExists(_channelName))
	{
		Channel* channel = server::getChannelByName(_channelName);
		if (channel->getInviteFlag() == 1)
		{
			if (channel->getIsOperator(_client->getNickName()) == true)
				channel->addInvited(server::getClientByFd(server::getClientFdByName(_nickName)));
			else if (channel->getIsMember(_client->getNickName()) == true)
				ERR_CHANOPRIVSNEEDED(_channelName);
		}
		else if (channel->getIsMember(_nickName) == true)
			ERR_USERONCHANNEL(_channelName);
	}
	_stringToSend.append(":" + _client->getIdenClient()+ " 341 : INVITE " + _nickName + " " + _channelName + "\r\n");
	Client* target = server::getClientByFd(server::getClientFdByName(_nickName));
	selfClientSend(_stringToSend, target->getFd());
}

void	Command::handleKick()
{
	if (_client->getIsregistered() == false) ERR_NOTREGISTERED();
	if (isInvalidChannelName(_vec[1])) ERR_NOSUCHCHANNEL();
		_channelName = _vec[1];
		// Check if is valid nick name
		if (validNick(_vec[2]) == false) ERR_ERRONEUSNICKNAME(_vec[2]);
		_nickName = _vec[2];
		// Read reason
		if (_size >= 4)
		{
			if (_vec[3][0] == ':') _reason = _vec[3].substr(1);
			else _reason = _vec[3];
			for (size_t i = 4; i < _size; i++) _reason += " " + _vec[i];
		}
		else _reason = "it's the wish of the channel operator";

	if (server::channelExists(_channelName) == false) ERR_NOSUCHCHANNEL();
	Channel *channel = server::getChannelByName(_channelName);
	if (channel->getIsMember(_nickName) == false) ERR_USERNOTINCHANNEL(_channelName, _nickName);
	if (_nickName == _client->getNickName()) ERR_CANTKICKYOURSELF();
	if (channel->getIsOperator(_client->getNickName()) == false) ERR_CHANOPRIVSNEEDED(_client->getNickName());
	Client* client = server::getClientByFd(server::getClientFdByName(_nickName));
	if (_channelName.size() != 0)
		_stringToSend = ":" + _client->getIdenClient() + " KICK " + _channelName + " " + _nickName + " :" + _reason + "\r\n";
	else
		_stringToSend = ":" + _client->getIdenClient() + " KICK " + _nickName + " :" + _reason + "\r\n";
	channel->removeUser(*client);
	selfClientSend(_stringToSend, client->getFd());
}

void	Command::handleMode()
{
	if (_size < 2) ERR_NEEDMOREPARAMS("MODE");
	if (_size > 3) ERR_SYNTAXPROBLEM();
	if (server::channelExists(_vec[1]) == false) ERR_NOSUCHCHANNEL();
	_channelName = _vec[1];
	_channelObj = server::getChannelByName(_channelName);
	if (_size > 2 && isValidMode(_vec[2]) == false) ERR_UMODEUNKNOWNFLAG();
	if (_size > 2) _mode = _vec[2];
	if (_mode.find("o") != std::string::npos && server::clientExists(_vec[3]) == false) ERR_NOSUCHNICK(_vec[3]);
	if (_size > 3)
		_parameter = _vec[3];
	// Add protection
	if (_channelObj)
	{
		if (_channelObj->getIsMember(_client->getNickName()) == false) ERR_NOTONCHANNEL();
		if (_channelObj->getIsOperator(_client->getNickName()) == false) ERR_NOPRIVILEGES(_channelName);
		_stringToSend = "324 :";
		switch (_mode[1])
		{
			case 'i': // Invite
				if (_mode[0] == '+') _channelObj->setInviteFlag(true);
				else _channelObj->setInviteFlag(false);
				break;
			case 't': // Topic restriction
				if (_mode[0] == '+') _channelObj->setTopicRestrictFlag(true);
				else _channelObj->setTopicRestrictFlag(false);
				break;
			case 'k': // Channel key
				if (_mode[0] == '+')
				{
					if (_parameter != "") _channelObj->setChanKey(_parameter);
					else ERR_NEEDMOREPARAMS("MODE");
				}
				else _channelObj->setChanKey("");
				break;
			case 'o': // Operator Privilige
				if (_mode[0] == '+')
				{
					if (_channelObj->getIsMember(_parameter) == true &&
					_channelObj->getIsOperator(_parameter) == false)
						_channelObj->addOperator(_channelObj->getMemberList()[_parameter]);
				}
				else _channelObj->removeOperator(*_channelObj->getOperatorList()[_parameter]);
				break;
			case 'l': // User Limit
				if (_mode[0] == '+')
				{
					if (_parameter != "" && stringIsNumeric(_parameter.c_str()) == true) _channelObj->setUserLimit(std::atoi(_parameter.c_str()));
					else if (_parameter == "") ERR_NEEDMOREPARAMS("MODE");
					else if (stringIsNumeric(_parameter.c_str()) == false) ERR_SYNTAXPROBLEM();
				}
				else _channelObj->setUserLimit(0);
				break;
		}
		_stringToSend.append(":" + _client->getIdenClient());
		_stringToSend.append(" " + _channelName);
		_stringToSend.append(" " + _mode);
		_stringToSend.append(" " + _parameter);
	}
	selfClientSend(_stringToSend, _client->getFd());
}

void	Command::handleQuit()
{
	if (!_client->getIsregistered()) ERR_NOTREGISTERED();
	if (_size > 1)
	{
		_reason += _vec[1].substr(1);
		for (size_t i = 2; i < _size; i++) _reason += " " + _vec[i];
	}
	std::vector<Channel*>	channelList = _client->getChannelList();
	if (channelList.size() > 0)
	{
		std::vector<Channel*>::iterator	tmpChannel = channelList.begin();
		std::vector<Channel*>::iterator	end = channelList.end();
		std::cout << "The client is member of the next channels: " << std::endl;
		for (; tmpChannel != end; ++tmpChannel)
		{
			std::string _reason = "no reason";
			if (_vec.size() > 1)
			{
				_reason = _vec[1];
				for (size_t i = 2; i < _vec.size(); i++) _reason += " " + _vec[i];
			}
			_stringToSend = _client->getIdenClient() + " leaves the channel [" + (*tmpChannel)->getName() + "] because " + _reason + "\r\n";
			Channel *channel = server::getChannelByName((*tmpChannel)->getName());
			if (channel != NULL)
			{
				sendToChannel(_stringToSend, (*tmpChannel)->getName());
				(*tmpChannel)->removeUser(*_client);
				if ((*tmpChannel)->getIsOperator(_client->getNickName()))
					(*tmpChannel)->removeOperator(*_client);
			}
		}
	}
	std::cout << "Client " << _client->getFd() << " disconnected" << std::endl;
	server::clientList.erase(_client->getFd());
	server::clientFDs.erase(server::clientFDs.begin() + _i);
	delete _client;
}
