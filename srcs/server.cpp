#include "server.hpp"

server::server(int port, std::string pass) : _serverIp("")
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

std::string	server::getPass() {return this->_pass;};
int			server::getSocketfd() {return this->_socketfd;};
int			server::getPort() {return this->_port;};

void server::handleClient()
{
	int					client_socketfd;
	socklen_t			client_len;
	struct sockaddr_in	client_address;
	char				buffer[256];
	char*				tmp;


	listen(this->_socketfd, 1);
	client_len = sizeof(client_address);
	client_socketfd = accept(this->_socketfd, (struct sockaddr *)&client_address, &client_len);
	if (!client_socketfd)
		throw std::logic_error("Failed to create Client socket");
	Client client((*this)._pass);
	while (true)
	{
		bzero(buffer, sizeof(buffer));
		recv(client_socketfd, buffer, 256, 0);
		std::cout << "Message Received: " << buffer << std::endl;
		std::vector<std::string> vec = getVector(buffer);
		if (vec.size() == 0) break;
		try
		{
			Command* cmd = getCommand(&client, vec);
			if (cmd == NULL)
			{
				bzero(buffer, sizeof(buffer));
				tmp = strdup("[ERROR]: UNSUPPORTED COMMAND\n");
			}
			else
			{
				tmp = cmd->execute();
				std::cout << "-----" << std::endl;
				delete cmd;
				std::cout << "|-----|" << std::endl;
			}
			bzero(buffer, sizeof(buffer));
		}
		catch (std::exception& e)
		{
			std::cout << "|-----|" << std::endl;
			tmp = strdup(e.what());
			bzero(buffer, sizeof(buffer));
			std::cout << "|-----|" << std::endl;
		}
		int sendStatus = send(client_socketfd, tmp, std::strlen(tmp), 0);
		if (sendStatus == -1)
		{
			delete tmp;
			break;
		}
		else delete tmp;
	}
	close(client_socketfd);
};

void	server::setServerIp(const std::string& ip) 
{
	_serverIp = ip;
}

const std::string&	server::getServerIp() const { return _serverIp; }