
/* We need to implement thoses function :
	join(user): This method adds a User object to the users list, signifying the user has joined the channel. It can potentially broadcast a join message to other users in the channel.
	part(user): This method removes a User object from the users list when the user leaves the channel. It can potentially broadcast a part message to other users in the channel.
	send_message(message): This method takes a Message object and broadcasts the message content to all users in the users list.
	get_users(): This method returns a list of all usernames or User objects currently joined in the channel.
*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Client.hpp"

class Client;

class Channel
{
private:
	/* data */
	std::string						_name; //String representing the channel name (e.g., "#programming")
	std::string						_topic; // String representing the current topic of the channel (optional)
	std::string						_chanKey; // String representing the current channel password (if "k" mode is set only)
	std::map<std::string, Client*>	_memberList; // List or set containing User objects currently joined in the channel
	std::map<std::string, Client*>	_operatorList; // List or set containing Operator level user objects currently joined in the channel
	std::map<std::string, Client*>	_invitedList; // List or set containing User objects currently invited to join the channel (Valid if +i)
	bool							_inviteFlag; // Boolean representing the flag for Invite only mode
	bool							_topicRestrictFlag; // Boolean representing the flag for restricting Topic changing to Operators only
	int								_userLimit; // Integer representing the Limit of user in a channel, 0 == no limit set
public:
	Channel(const std::string& name);

	Channel& operator=(const Channel& other);

	// Set the channel name (consider security implications)
	void setName(const std::string& name);

	// Get the channel name
	const std::string& getName() const;

	// Set the channel topic
	void setTopic(const std::string& topic);

	// Get the channel topic
	const std::string& getTopic() const;

	// Get channel key
	const std::string& getChanKey() const;

	// Set channel key
	void setChanKey(const std::string& key);

	// Get invite flag
	const bool& getInviteFlag() const;

	// Set invite flag
	void setInviteFlag(const bool& flag);

	// Get topic restrict flag
	const bool& getTopicRestrictFlag() const;

	// Set topic restrict flag
	void setTopicRestrictFlag(const bool& flag);

	// Get user limit
	const int& getUserLimit() const;

	// Set user limit
	void setUserLimit(const int& limit);

	bool getIsMember(const std::string &name) const;

	bool getIsOperator(const std::string &name) const;

	bool hasUser(const Client& client) const;

	void removeUser(const Client& client);

	void addMember(Client *client);

	void removeOperator(const Client& client);

	void addOperator(Client *client);

	void removeInvited(const Client& client);

	void addInvited(Client *client);

	//	Get a list of usernames in the channel
//   std::vector<std::string> getUsernames() const;

	std::string getClientList() const;

	std::map<std::string, Client*>& getMemberList();

	std::map<std::string, Client*>& getOperatorList();

	std::map<std::string, Client*>& getInvitedList();

	~Channel();
};
