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
#include <csignal>
#include <cerrno>
#include "Command.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define NOFLAG 0
#define PARTING 1
#define QUITING 2

struct message
{
	std::string data;
	int			flag;
};

class server
{
	static std::string		_hostname;
	static std::string		_serverIp;
	static std::string		_creationTime;
	static bool				_finish;
	private:
		struct sockaddr_in	_address;
		std::string			_pass;
		int					_socketfd;
		int					_port;

	public:
		static	std::multimap<int, struct message>	messageList;
		static	std::map<std::string, Channel*>		channelList;
		static	std::map<int, Client*>				clientList;
		static	std::vector<pollfd>					clientFDs;
		server(int port, std::string pass);
		~server();

		void handleClient();
		std::string									getPass();
		int											getSocketfd();
		int											getPort();
		void										setServerIp(const std::string& ip);
		static bool									channelExists(const std::string& channelName);
		static void									addChannel(Channel *channel);
		static void									removeChannel(std::string channelName);
		static void									addClient(Client *client);
		static std::map<int, Client*>&				getClientList();
		static std::map<std::string, Channel*>&		getChannelList();
		static	std::multimap<int, struct message>&	getMessageList();
		static Channel*								getChannelByName(const std::string& channelName);
		static Client*								getClientByFd(int fd);
		static bool									clientExists(const std::string& clientName);
		static int									getClientFdByName(const std::string& clientName);
		static std::string&							getServerIp();
		static void									setFinished(bool status);
		void										setHostname(const std::string& hostname);
		static std::string&							getHostname();
		void										setCreationTime(const std::string& timestamp);
		static std::string&							getCreationTime();
		void										displayInstructions();
};
