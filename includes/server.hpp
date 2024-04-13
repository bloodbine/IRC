#pragma once

#include <string>
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
#include "Command.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class server
{
	private:
		struct sockaddr_in _address;
		std::string _pass;
		std::string	_serverIp;
		std::map<std::string, Channel*>	_channelList;
		int _socketfd;
		int _port;

	public:
		server(int port, std::string pass);
		~server();

		void handleClient();

		std::string		getPass();
		int				getSocketfd();
		int				getPort();
		void			setServerIp(const std::string& ip);
		bool			channelExists(const std::string& channelName) const;
		void			addChannel(Channel *channel);
		const std::string&			getServerIp() const;
};
