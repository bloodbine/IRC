#include "server.hpp"
#include <cstring>
#include <stdexcept>
#include <sys/socket.h>

server::server(int port, std::string pass)
{
	if (!port || port <= 0)
		throw std::logic_error("Missing or Invalid Port");
	if (pass.empty())
		throw std::logic_error("Missing Password");
	this->_port = port;
	this->_pass = pass;
	bzero((char *)&this->_address, sizeof(this->_address));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	std::cout << this->_port << std::endl;
	this->_address.sin_port = htons(this->_port);
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socketfd == -1)
		throw std::logic_error("Failed to create Server socket");
	if (bind(this->_socketfd, (struct sockaddr *)&this->_address, sizeof(this->_address)) != 0)
		throw std::logic_error("Failed to bind Socket");
};

server::~server()
{
	close(this->_socketfd);
};

std::string	server::get_pass() {return this->_pass;};
int			server::get_socketfd() {return this->_socketfd;};
int			server::get_port() {return this->_port;};

void server::handle_client()
{
	int					client_socketfd;
	socklen_t			client_len;
	struct sockaddr_in	client_address;
	char				buffer[256];
	std::string			tmp;


	listen(this->_socketfd, 1);
	client_len = sizeof(client_address);
	client_socketfd = accept(this->_socketfd, (struct sockaddr *)&client_address, &client_len);
	if (!client_socketfd)
		throw std::logic_error("Failed to create Client socket");
	while (true)
	{
		recv(client_socketfd, buffer, 256, 0);
		std::cout << "Message Received: " << buffer << std::endl;
		if (strncmp(buffer, "CAP LS", 6) == 0) tmp = "PONG 127.0.0.1";
		else if (strlen(buffer) == 0) break ;
		send(client_socketfd, tmp.c_str(), std::strlen(buffer), 0);
		bzero(buffer, sizeof(buffer));
	}
	close(client_socketfd);
};
