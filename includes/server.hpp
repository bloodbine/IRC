#pragma once

#include <string>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include "Command.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class server
{
	static	std::map<std::string, Channel*>		channelList;
	static	std::map<int, Client*>				_clientList;
	static	std::vector<pollfd>					_clientFDs;
	static	std::string _hostname;
	static	std::string	_serverIp;
	static	std::string _creationTime;
	private:
		struct sockaddr_in _address;
		std::string _pass;
		int _socketfd;
		int _port;
		bool	_finish;

	public:
		server(int port, std::string pass);
		~server();

		void handleClient();
		std::string					getPass();
		int							getSocketfd();
		int							getPort();
		void						setServerIp(const std::string& ip);
		static bool					channelExists(const std::string& channelName);
		static void					addChannel(Channel *channel);
		static void					removeChannel(std::string channelName);
		static void					addClient(Client *client);
		static Channel*				getChannelByName(const std::string& channelName);
		static Client*				getClientByFd(int fd);
		static bool					clientExists(const std::string& clientName);
		static int					getClientFdByName(const std::string& clientName);
		static std::string&			getServerIp();
		void						setHostname(const std::string& hostname);
		static std::string&			getHostname();
		void						setCreationTime(const std::string& timestamp);
		static std::string&			getCreationTime();
		int							customSend(char *tmp, int i, bool failedToSendMsg, std::vector<std::string> vec);
		int							runNormalCommand(std::vector<std::string>& vec, int i, bool failedToSendMsg);
		void						handleQuit(std::vector<std::string> vec, int i);
		void						handleShutdown(std::vector<std::string> vec);
};
