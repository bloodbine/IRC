#pragma once

#include <string>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <stdexcept>
#include <libc.h>
#include "Command.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class server
{
	static std::map<std::string, Channel*>		channelList;
	static std::map<int, Client*>				_clientList;
	static std::vector<pollfd>					_clientFDs;
	private:
		struct sockaddr_in _address;
		std::string _pass;
		std::string	_serverIp;
		int _socketfd;
		int _port;

	public:
		server(int port, std::string pass);
		~server();

		void handleClient();

		std::string					getPass();
		int							getSocketfd();
		int							getPort();
		int							customSend(bool failedToSendMsg, char **tmp, std::string vec, int i);
		void						setServerIp(const std::string& ip);
		static bool					channelExists(const std::string& channelName);
		static void					addChannel(Channel *channel);
		static void					addClient(Client *client);
		static Channel*				getChannelByName(const std::string& channelName);
		static Client*				getClientByFd(int fd);
		static bool					clientExists(const std::string& clientName);
		int							getClientFdByName(const std::string& clientName);
		const std::string&			getServerIp() const;
		int							runNormalCommand(std::vector<std::string>& vec, int i);
		int							runPrivmsgCommand(std::vector<std::string>& vec, int i);
		int							runJoinCommand(std::vector<std::string>& vec, int i);
};
