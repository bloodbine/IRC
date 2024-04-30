
#include "Channel.hpp"

Channel::Channel(const std::string& name) : _name(name), _topic("No topic is set"), _chanKey(""), _inviteFlag(false), _topicRestrictFlag(false), _userLimit(0) {}

Channel::~Channel()
{}

void Channel::setName(const std::string& name) { _name = name; }

// Get the channel name
const std::string& Channel::getName() const { return _name; }

// Set the channel topic
void Channel::setTopic(const std::string& topic) { _topic = topic; }

// Get the channel topic
const std::string& Channel::getTopic() const { return _topic; }

// Get channel key
const std::string& Channel::getChanKey() const { return _chanKey; };

// Set channel key
void Channel::setChanKey(const std::string& key) { _chanKey = key;};

// Get invite flag
const bool& Channel::getInviteFlag() const { return _inviteFlag; };

// Set invite flag
void Channel::setInviteFlag(const bool& flag) { _inviteFlag = flag; };

// Get topic restrict flag
const bool& Channel::getTopicRestrictFlag() const { return _topicRestrictFlag; };

// Set topic restrict flag
void Channel::setTopicRestrictFlag(const bool& flag) { _topicRestrictFlag = flag; };

// Get user limit
const int& Channel::getUserLimit() const { return _userLimit; };

// Set user limit
void Channel::setUserLimit(const int& limit) { _userLimit = limit; };

// bool Channel::hasUser(const Client& client) const 
// {
// 	return (std::find(_memberList.begin(), _memberList.end(), client) != _memberList.end());
// }

bool Channel::hasUser(const Client& client) const
{
	for (std::map<std::string, Client*>::const_iterator it = _memberList.begin(); it != _memberList.end(); ++it) {
		if (it->first == client.getNickName()) { // Compare nicknames
			return true;
		}
	}
	return false;
}

bool Channel::getIsMember(const std::string &name) const { return _memberList.find(name) != _memberList.end(); }

bool Channel::getIsOperator(const std::string &name) const { return _operatorList.find(name) != _operatorList.end(); }

void Channel::removeUser(const Client& client)
{
	// Find the client member list using nickname
	std::map<std::string, Client*>::iterator it = _memberList.find(client.getNickName());
	// If client found remove key-value pair from the map
	if (it != _memberList.end())
		_memberList.erase(it);
	// if (it == _memberList.end()) ERR_USERNOTINCHANNEL(_name, client.getNickName());
	// else
	// 	ERR_CHANOPRIVSNEEDED(_name);
}

void Channel::addMember(Client *client)
{
	_memberList[client->getNickName()] = client;
}

void Channel::removeOperator(const Client& client)
{
	// Find the client member list using nickname
	std::map<std::string, Client*>::iterator it = _operatorList.find(client.getNickName());
	// If client found remove key-value pair from the map
	if (it != _operatorList.end())
		_operatorList.erase(it);
}

void Channel::addOperator(Client *client)
{
	_operatorList[client->getNickName()] = client;
}

void Channel::removeInvited(const Client& client)
{
	// Find the client member list using nickname
	std::map<std::string, Client*>::iterator it = _operatorList.find(client.getNickName());
	// If client found remove key-value pair from the map
	if (it != _operatorList.end())
		_operatorList.erase(it);
}

void Channel::addInvited(Client *client)
{
	_invitedList[client->getNickName()] = client;
}

std::string Channel::getClientList() const
{
	std::string out;
	std::pair<std::string, Client*>  tmp;
	std::map<std::string, Client*>::const_iterator itr = _memberList.begin();
	std::map<std::string, Client*>::const_iterator end = _memberList.end();
	int i = 0;
	for (; itr != end; ++itr)
	{
		tmp = *itr;
		if (i > 0)
			out += " @" + tmp.second->getNickName();
		else out += "@" + tmp.second->getNickName();
		i++;
	}
	return out;
}

std::map<std::string, Client*>& Channel::getMemberList() { return _memberList; }

std::map<std::string, Client*>& Channel::getOperatorList() { return _operatorList; }

std::map<std::string, Client*>& Channel::getInvitedList() { return _invitedList; }


// bool Channel::doKickFromChannel(int fd, int userFd, string userName){
//     if (fd == userFd) {
//         string err = "You can't KICK yourself\r\r\n";
//         send(fd, err.c_str(), err.length() + 1, 0);
//         return false;
//     }
// 	if (fd == _fdAdmin){
// 		vector<int>::iterator itb = _fds.begin();
// 		vector<int>::iterator ite = _fds.end();
// 		vector<int>::iterator it;
// 		for (it = itb; it != ite; it++){
// 			if ((*it) == userFd){
// 				_fds.erase(it);
// 				return true;
// 			}
// 		}
// 	if (it == ite) {
// 		string err = "441 * " + userName +  _channelName + " :They aren't on that channel\r\n";
// 		send(fd, err.c_str(), err.length() + 1, 0);
// 		return false;
// 	}
// 	} else {
// 		string err = "482 *  " + _channelName + " :You're not channel operator\r\n";
// 		send(fd, err.c_str(), err.length() + 1, 0);
// 		return false;
// 	}
// 	return false;
// }