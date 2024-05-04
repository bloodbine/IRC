#pragma once

#include <string>
#include <vector>

class server;
class Client;

class Command
{
private:
	Client*	_client;
	std::vector<std::string>	_vec;
	size_t	_size;
	int	_cmdType;
	std::string	_stringToSend;
	std::string	_nickName;
	std::string	_userName;
	std::string	_realName;
	std::string	_channelName;
	std::string	_chanKey;
	std::string	_reasson;
	std::string	_serverName;
	std::string _topic;
	std::string _msg;
	std::string _target;
	bool		_targetIsChannel;
	bool		_clearTopic;

	void	handlePass();
	void	handleNick();
	void	handleUser();
	void	handleJoin();
	void	handlePart();
	void	handlePing();
	void	handleNotice();
	void	handleTopic();
	void	handlePrivmsg();
	void	handleInvite();

public:
	Command(const std::vector<std::string>& vec, Client *client);
	void	printStringToSend() const;
	~Command();
};