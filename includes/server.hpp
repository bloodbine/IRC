#pragma once

#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "Command.hpp"
#include "utils.hpp"


class server
{
	private:
		struct sockaddr_in _address;
		std::string _pass;
		int _socketfd;
		int _port;

	public:
		server(int port, std::string pass);
		~server();

		void handle_client();

		std::string		get_pass();
		int				get_socketfd();
		int				get_port();
};
