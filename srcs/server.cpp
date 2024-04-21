#include "server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <fcntl.h>
#include <utility>

std::map<std::string, Channel*>	server::channelList;
std::map<int, Client*>			server::_clientList;
std::vector<pollfd>				server::_clientFDs;

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
	// fcntl(this->_socketfd, F_SETFL, O_NONBLOCK);
	if (this->_socketfd == -1)
		throw std::logic_error("Failed to create Server socket");
	if (bind(this->_socketfd, (struct sockaddr *)&this->_address, sizeof(this->_address)) != 0)
		throw std::logic_error("Failed to bind Socket");
	pollfd server;
	server.fd = this->_socketfd;
	server.events = POLLIN;
	this->_clientFDs.push_back(server);
};

server::~server()
{
	close(this->_socketfd);
};

std::string	server::getPass() {return this->_pass;};
int			server::getSocketfd() {return this->_socketfd;};
int			server::getPort() {return this->_port;};

			// Channel tmpChannel("hola", "tmpTopic", "TmpMode");
			// std::cout << "'hola' is in _channelList: " << channelExists(tmpChannel.getName()) << std::endl;
			// std::cout << "Adding 'hola' to _channelList" << std::endl;
			// addChannel(&tmpChannel);
			// std::cout << "channel list: \n";
			// for (std::map<std::string, Channel*>::iterator itr = _channelList.begin(); itr != _channelList.end(); ++itr)
			// {
			// 	std::pair<std::string, Channel*> p = *itr;
			// 	std::cout << p.first<< ": " << p.second->getName() << std::endl;
			// }

// void server::handleClient()
// {
// 	int					client_socketfd;
// 	socklen_t			client_len;
// 	struct sockaddr_in	client_address;
// 	char				buffer[256];
// 	char*				tmp;


// 	listen(this->_socketfd, 1);
// 	client_len = sizeof(client_address);
// 	client_socketfd = accept(this->_socketfd, (struct sockaddr *)&client_address, &client_len);
// 	if (!client_socketfd)
// 		throw std::logic_error("Failed to create Client socket");
// 	Client client((*this)._pass, client_socketfd);
// 	while (true)
// 	{
// 		bzero(buffer, sizeof(buffer));
// 		recv(client_socketfd, buffer, 256, 0);
// 		std::cout << "Message Received: " << buffer << std::endl;
// 		std::vector<std::string> vec = getVector(buffer);
// 		if (vec.size() == 0) break;
// 		try
// 		{
// 			Command* cmd = getCommand(&client, vec);
// 			if (cmd == NULL)
// 			{
// 				bzero(buffer, sizeof(buffer));
// 				tmp = strdup("[ERROR]: UNSUPPORTED COMMAND\n");
// 			}
// 			else
// 			{
// 				tmp = cmd->execute();
// 				delete cmd;
// 			}
// 			bzero(buffer, sizeof(buffer));
// 		}
// 		catch (std::exception& e)
// 		{
// 			tmp = strdup(e.what());
// 			bzero(buffer, sizeof(buffer));
// 		}
// 		int sendStatus = send(client_socketfd, tmp, std::strlen(tmp), 0);
// 		if (sendStatus == -1)
// 		{
// 			delete tmp;
// 			break;
// 		}
// 		delete tmp;
// 	}
// 	close(client_socketfd);
// };

int	server::runNormalCommand(std::vector<std::string>& vec, int i)
{
	char *tmp;
	try
	{
		Command* cmd = getCommand(this->_clientList[this->_clientFDs[i].fd], vec);
		if (cmd == NULL)
		{
			tmp = strdup("[ERROR]: UNSUPPORTED COMMAND\n");
			return -1;
		}
		else
		{
			tmp = cmd->execute();
			delete cmd;
		}
	}
	catch (std::exception& e)
	{
		tmp = strdup(e.what());
	}
	int sendStatus = send(this->_clientFDs[i].fd, tmp, std::strlen(tmp), 0);
	delete tmp;
	if (sendStatus == -1)
		return -1;
	return 0;
}

int							server::getClientFdByName(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; ++itr) {
		if ((*itr).second->GetNickName() == clientName) return (*itr).first;
	}
	return -1;
}


int	server::runPrivmsgCommand(std::vector<std::string>& vec, int i)
{
	bool	failedToSendMsg = false;
	char *tmp;
	try
	{
		Command* cmd = getCommand(this->_clientList[this->_clientFDs[i].fd], vec);
		if (cmd == NULL)
		{
			tmp = strdup("[ERROR]: UNSUPPORTED COMMAND\n");
			return -1;
		}
		else
		{
			tmp = cmd->execute();
			delete cmd;
		}
	}
	catch (std::exception& e)
	{
		tmp = strdup(e.what());
		failedToSendMsg = true;
	}

	int	toSendFd;
	if (failedToSendMsg) toSendFd = this->_clientFDs[i].fd;
	else toSendFd = getClientFdByName(vec[1]);
	std::cout << "privmsg to fd: " << toSendFd << std::endl;
	int	sendStatus = send(toSendFd, tmp, std::strlen(tmp), 0);
	delete tmp;
	if (sendStatus == -1)
		return -1;
	return 0;
}

void server::handleClient()
{
	listen(this->_socketfd, 5);
	while (42)
	{
		int ret = poll(&this->_clientFDs[0], this->_clientFDs.size(), -1);
		if (ret == -1)
		{
			perror("poll");
			break;
		}
		if (this->_clientFDs[0].revents == POLLIN)
		{
			sockaddr_in incClientAddr;
			socklen_t incClientAddrLen = sizeof(incClientAddr);
			int incClientSocket = accept(this->_socketfd,
			reinterpret_cast<sockaddr*>(&incClientAddr),
			&incClientAddrLen);
			if (incClientSocket != -1)
			{
				pollfd incClientTemp;
				incClientTemp.fd = incClientSocket;
				incClientTemp.revents = POLLIN;
				// fcntl(incClientTemp.fd, F_SETFL, O_NONBLOCK);
				this->_clientFDs.push_back(incClientTemp);
				this->_clientList.insert(std::pair<int, Client*>(incClientTemp.fd, new Client(this->_pass, incClientTemp.fd)));
				std::cout << "New Client " << incClientTemp.fd << " connected : " << inet_ntoa(incClientAddr.sin_addr) << std::endl;
			}
		}

		for (unsigned int i = 1; i < this->_clientFDs.size(); ++i)
		{
			if (this->_clientFDs[i].revents & POLLIN)
			{
				char buffer[1024];
				bzero(buffer, sizeof(buffer));
				int bytesRead = recv(this->_clientFDs[i].fd, buffer, 1024, 0);
				switch(bytesRead)
				{
					case -1:
						std::cerr << "Client " << this->_clientFDs[i].fd << " error: ";
						perror("recv");
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						break;
					case 0:
						std::cout << "Client " << this->_clientFDs[i].fd << " disconnected" << std::endl;
						close(this->_clientFDs[i].fd);
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						break;
					default:
						std::cout << "Recieved message from Client " << this->_clientFDs[i].fd << std::endl;
						std::cout << std::string(buffer);
					std::vector<std::string> vec = getVector(buffer);
					if (vec[0] == "PRIVMSG" && runPrivmsgCommand(vec, i) == -1) break;
					else if (runNormalCommand(vec, i) == -1) break;
				}
			}
		}
	}
};

void	server::setServerIp(const std::string& ip) 
{
	_serverIp = ip;
}

const std::string&	server::getServerIp() const { return _serverIp; }

bool	server::channelExists(const std::string& channelName)
{
	return (channelList.find(channelName) != channelList.end());
}

void	server::addChannel(Channel *channel)
{
	channelList[channel->getName()] = channel;
}

Channel* server::getChannelByName(const std::string& channelName)
{
	return channelList[channelName];
}

void	server::addClient(Client *client)
{
	_clientList[client->getFd()] = client;
}

Client* server::getClientByFd(int fd)
{
	return _clientList[fd];
}

bool	server::clientExists(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; ++itr) {
		if ((*itr).second->GetNickName() == clientName) return true;
	}
	return (false);
}
