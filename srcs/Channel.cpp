
#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& topic, const std::string& mode) : _name(name), _topic(topic), _mode(mode) {}

Channel::~Channel()
{
}

void Channel::setName(const std::string& name) { _name = name; }

// Get the channel name
const std::string& Channel::getName() const { return _name; }

// Set the channel topic
void Channel::setTopic(const std::string& topic) { _topic = topic; }

// Get the channel topic
const std::string& Channel::getTopic() const { return _topic; }

// Set the channel mode
void Channel::setMode(const std::string& mode) { _mode = mode; }

// Get the channel mode
const std::string& Channel::getMode() const { return _mode; }

// bool Channel::hasUser(const Client& client) const 
// {
// 	return (std::find(_memberList.begin(), _memberList.end(), client) != _memberList.end());
// }

bool Channel::hasUser(const Client& client) const
{
    for (std::map<std::string, Client*>::const_iterator it = _memberList.begin(); it != _memberList.end(); ++it) {
        if (it->first == client.GetNickName()) { // Compare nicknames
            return true;
        }
    }
    return false;
}


bool  Channel::getIsMember(const std::string &name) const { return _memberList.find(name) != _memberList.end(); }

void  Channel::addMember(Client *client)
{
	_memberList[client->GetNickName()] = client;
}