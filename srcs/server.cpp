#include "server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <fcntl.h>
#include <utility>

std::multimap<int, std::string>		server::messageList;
std::map<std::string, Channel*>	server::channelList;
std::map<int, Client*>			server::clientList;
std::vector<pollfd>				server::clientFDs;
std::string						server::_hostname;
std::string						server::_serverIp;
std::string						server::_creationTime;
bool							server::_finish;

server::server(int port, std::string pass)
{
	try
	{
		if (!port || port <= 0)
			throw std::logic_error("Missing or Invalid Port");
		if (pass.empty())
			throw std::logic_error("Missing Password");
		_port = port;
		_pass = pass;
		bzero((char *)&_address, sizeof(_address));
		_address.sin_family = AF_INET;
		_address.sin_addr.s_addr = INADDR_ANY;
		inet_pton(AF_INET, "0.0.0.0", &_address.sin_addr);
		std::cout << _port << std::endl;
		_address.sin_port = htons(_port);
		_socketfd = socket(AF_INET, SOCK_STREAM, 0);
		int enable = 1;
		linger lin;
		lin.l_onoff = 0;
		lin.l_linger = 0;
		if (_socketfd == -1)
			throw std::logic_error("Failed to create Server socket");
		if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
			throw std::logic_error(std::string((char *)("Failed to set Server socket Address option: ")) + std::string(strerror(errno)));
		if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable)) == -1)
			throw std::logic_error(std::string((char *)"Failed to set Server socket Port option"));
		if (setsockopt(_socketfd, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin)) == -1)
			throw std::logic_error(std::string((char *)"Failed to set Server socket Linger option"));
		if (fcntl(_socketfd, F_SETFL, O_NONBLOCK) == -1)
			throw std::logic_error("Failed to set Server socket Non-Block flag");
		if (bind(_socketfd, (struct sockaddr *)&_address, sizeof(_address)) == -1)
			throw std::logic_error("Failed to bind Socket");
		pollfd server;
		server.fd = _socketfd;
		server.events = POLLIN;
		server.revents = 0;
		clientFDs.push_back(server);
		addrStructToString(_serverIp, _hostname);
		std::cerr << "Host and IP: " << _hostname << " " << _serverIp << std::endl;
		_creationTime = getTimestamp();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
};

server::~server() { close(_socketfd); }

std::string	server::getPass() {return _pass;};
int			server::getSocketfd() {return _socketfd;};
int			server::getPort() {return _port;};

int	server::getClientFdByName(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = clientList.begin();
	std::map<int, Client*>::iterator end = clientList.end();
	for (; itr != end; itr++) {
		if ((*itr).second->getNickName() == clientName) return (*itr).first;
	}
	return -1;
}

void server::handleClient()
{
	std::signal(SIGINT, signal_handler);
	if (listen(_socketfd, 5) == -1)
	{
		perror("listen");
		exit(1);
	}
	while (!_finish)
	{
		int ret = poll(&clientFDs[0], clientFDs.size(), -1);
		if (ret == -1)
		{
			perror("poll");
			break;
		}
		if (clientFDs[0].revents & POLLIN)
		{
			sockaddr_in incClientAddr;
			socklen_t incClientAddrLen = sizeof(incClientAddr);
			int incClientSocket = accept(_socketfd,
			reinterpret_cast<sockaddr*>(&incClientAddr),
			&incClientAddrLen);
			if (incClientSocket != -1)
			{
				pollfd incClientTemp;
				incClientTemp.fd = incClientSocket;
				incClientTemp.events = POLLIN | POLLOUT;
				incClientTemp.revents = 0;
				if (fcntl(incClientTemp.fd, F_SETFL, O_NONBLOCK) == -1)
					perror("fcntl");
				clientFDs.push_back(incClientTemp);
				clientList.insert(std::pair<int, Client*>(incClientTemp.fd, new Client(_pass, incClientTemp.fd)));
				std::cout << "New Client " << incClientTemp.fd << " connected : " << inet_ntoa(incClientAddr.sin_addr) << std::endl;
				clientFDs[0].revents = 0;
			}
		}

		for (unsigned int i = 1; i < clientFDs.size(); ++i)
		{
			if (clientFDs[i].revents & POLLIN)
			{
				Client *client = clientList[clientFDs[i].fd];
				char buffer[1024];
				bzero(buffer, sizeof(buffer));
				int bytesRead = recv(clientFDs[i].fd, buffer, 1024, 0);
				std::vector<Channel*>	clientChannelList = client->getChannelList();
				switch(bytesRead)
				{
					case -1:
						std::cerr << "Client " << clientFDs[i].fd << " error: ";
						std::cerr << errno << " ";
						perror("recv");
						clientList.erase(clientFDs[i].fd);
						clientFDs.erase(clientFDs.begin() + i);
						delete client;
						break;
					case 0:
						std::cout << "Client " << clientFDs[i].fd << " disconnected" << std::endl;
						close(clientFDs[i].fd);
						clientList.erase(clientFDs[i].fd);
						clientFDs.erase(clientFDs.begin() + i);
						if (clientChannelList.size() > 0)
						{
							std::vector<Channel*>::iterator	tmpChannel = clientChannelList.begin();
							std::vector<Channel*>::iterator	end = clientChannelList.end();
							for (; tmpChannel != end; ++tmpChannel)
							{
								Channel *channel = server::getChannelByName((*tmpChannel)->getName());
								if (channel != NULL)
								{
									(*tmpChannel)->removeUser(*client);
									if ((*tmpChannel)->getIsOperator(client->getNickName()))
										(*tmpChannel)->removeOperator(*client);
								}
							}
						}
						delete client;
						break;
					default:
						std::string	tmp(buffer);
						
						while (tmp.find('\n') == std::string::npos)
						{
							bzero(buffer, sizeof(buffer));
							bytesRead = recv(clientFDs[i].fd, buffer, 1024, 0);
							tmp += buffer;
						}
						std::vector<std::string>	vec = getVector((char *)(tmp.c_str()));
						try
						{
							if (vec.size() > 0) Command	cmd(vec, client, i);
						}
						catch (std::exception& e)
						{
							// Needs to do something else in case it failes to send
							selfClientSend(e.what(), clientFDs[i].fd);
						}
						break ;
				}
			}
			if (clientFDs[i].revents & POLLOUT && messageList.size() != 0)
			{
				std::multimap<int, std::string>::iterator message = messageList.equal_range(clientFDs[i].fd).first;
				if (message != server::messageList.end())
				{
					int senderr = send(clientFDs[i].fd, (message->second).c_str(), (message->second).length(), 0);
					if (senderr < 0)
						perror("send");
					else
						messageList.erase(message);
				}
			}
			clientFDs[i].revents = 0;
		}
	}
};

void			server::setServerIp(const std::string& ip) { _serverIp = ip; }

std::string&	server::getServerIp()  { return _serverIp; }

void			server::setHostname(const std::string& hostname) { _hostname = hostname; }

std::string&	server::getHostname()  { return _hostname; }

void			server::setCreationTime(const std::string& timestamp) { _creationTime = timestamp; }

std::string&	server::getCreationTime()  { return _creationTime; };

bool			server::channelExists(const std::string& channelName){ return (channelList.find(channelName) != channelList.end()); }

void	server::addChannel(Channel *channel) { channelList[channel->getName()] = channel; }

void	server::removeChannel(std::string channelName) 
{
	if (channelExists(channelName))
	{
		channelList.erase(channelName);
		delete channelList[channelName];
	}
}

Channel* server::getChannelByName(const std::string& channelName) {
	if (channelList.size() > 0)
	{
		std::map<std::string, Channel*>::iterator	 it = channelList.find(channelName);
		if (it != channelList.end()) {
			return it->second;
		}
	}
	return NULL;
}

void	server::addClient(Client *client) { clientList[client->getFd()] = client; }

Client* server::getClientByFd(int fd)
{
	std::map<int, Client*>::iterator	 it = clientList.find(fd);
	if (it != clientList.end()) {
		return it->second;
	} else {
		return NULL;
	}
}

bool	server::clientExists(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = clientList.begin();
	std::map<int, Client*>::iterator end = clientList.end();
	for (; itr != end; ++itr) {
		if ((*itr).second->getNickName() == clientName) return true;
	}
	return (false);
}

std::map<int, Client*>	server::getClientList() { return clientList; }
std::map<std::string, Channel*>	server::getChannelList() { return channelList; }
std::multimap<int, std::string>	server::getMessageList() { return messageList; }
void server::setFinished(bool status) { _finish = status; }