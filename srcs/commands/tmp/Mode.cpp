#include "commands/Mode.hpp"
#include "server.hpp"

Mode::Mode(Client* client, const std::vector<std::string>& vec) : _client(client), _channelObj(NULL), _size(vec.size()), _channel(""), _mode(""), _parameter("")
{
	if (_size < 2) ERR_NEEDMOREPARAMS("MODE");
	if (server::channelExists(vec[1]) == false) ERR_NOSUCHCHANNEL();
	_channel = vec[1];
	_channelObj = server::getChannelByName(_channel);
	if (_size > 2 && isValidMode(vec[2]) == false) ERR_UMODEUNKNOWNFLAG();
	if (_size > 2) _mode = vec[2];
	if (_mode.find("o") != std::string::npos && server::clientExists(vec[3]) == false) ERR_NOSUCHNICK(vec[3]);
	if (_size > 3)
		_parameter = vec[3];
	if (_channelObj->getIsMember(_client->getNickName()) == false) ERR_NOTONCHANNEL();
	if (_channelObj->getIsOperator(_client->getNickName()) == false) ERR_NOPRIVILEGES(_channel);
}

std::string Mode::execute() const
{
	if (_size < 3)
		return "";
	std::string tmp = "324 :";
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
	tmp.append(":" + _client->getIdenClient());
	tmp.append(" " + _channel);
	tmp.append(" " + _mode);
	tmp.append(" " + _parameter);
	return tmp;
}

Mode::~Mode() {}