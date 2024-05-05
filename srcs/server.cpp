#include "server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <fcntl.h>
#include <utility>

std::map<std::string, Channel*>	server::channelList;
std::map<int, Client*>			server::_clientList;
std::vector<pollfd>				server::_clientFDs;
std::string						server::_hostname;
std::string						server::_serverIp;
std::string						server::_creationTime;

server::server(int port, std::string pass) : _finish(false)
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
	inet_pton(AF_INET, "0.0.0.0", &_address.sin_addr);
	std::cout << this->_port << std::endl;
	this->_address.sin_port = htons(this->_port);
	this->_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	int enable = 1;
	linger lin;
	lin.l_onoff = 0;
	lin.l_linger = 0;
	if (this->_socketfd == -1)
		throw std::logic_error("Failed to create Server socket");
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
		throw std::logic_error(std::string((char *)("Failed to set Server socket Address option: ")) + std::string(strerror(errno)));
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable)) == -1)
		throw std::logic_error(std::string((char *)"Failed to set Server socket Port option"));
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin)) == -1)
		throw std::logic_error(std::string((char *)"Failed to set Server socket Linger option"));
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) == -1)
		throw std::logic_error("Failed to set Server socket Non-Block flag");
	if (bind(this->_socketfd, (struct sockaddr *)&this->_address, sizeof(this->_address)) == -1)
		throw std::logic_error("Failed to bind Socket");
	pollfd server;
	server.fd = this->_socketfd;
	server.events = POLLIN;
	server.revents = 0;
	this->_clientFDs.push_back(server);
	addrStructToString(_serverIp, _hostname);
	std::cerr << "Host and IP: " << _hostname << " " << _serverIp << std::endl;
	_creationTime = getTimestamp();
};

server::~server() { close(this->_socketfd); }

std::string	server::getPass() {return this->_pass;};
int			server::getSocketfd() {return this->_socketfd;};
int			server::getPort() {return this->_port;};

int							server::getClientFdByName(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; itr++) {
		if ((*itr).second->getNickName() == clientName) return (*itr).first;
	}
	return -1;
}



void server::handleClient()
{
	std::signal(SIGINT, signal_handler);
	listen(this->_socketfd, 5);
	while (!_finish)
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
				incClientTemp.events = POLLIN;
				incClientTemp.revents = 0;
				if (fcntl(incClientTemp.fd, F_SETFL, O_NONBLOCK) == -1)
					perror("fcntl");
				this->_clientFDs.push_back(incClientTemp);
				this->_clientList.insert(std::pair<int, Client*>(incClientTemp.fd, new Client(this->_pass, incClientTemp.fd)));
				std::cout << "New Client " << incClientTemp.fd << " connected : " << inet_ntoa(incClientAddr.sin_addr) << std::endl;
				this->_clientFDs[0].revents = 0;
			}
		}

		for (unsigned int i = 1; i < this->_clientFDs.size(); ++i)
		{
			if (this->_clientFDs[i].revents & POLLIN)
			{
				Client *client = this->_clientList[this->_clientFDs[i].fd];
				char buffer[1024];
				bzero(buffer, sizeof(buffer));
				int bytesRead = recv(this->_clientFDs[i].fd, buffer, 1024, 0);
				this->_clientFDs[i].revents = 0;
				switch(bytesRead)
				{
					case -1:
						std::cerr << "Client " << this->_clientFDs[i].fd << " error: ";
						std::cerr << errno << " ";
						perror("recv");
						this->_clientList.erase(this->_clientFDs[i].fd);
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						delete client;
						break;
					case 0:
						std::cout << "Client " << this->_clientFDs[i].fd << " disconnected" << std::endl;
						close(this->_clientFDs[i].fd);
						this->_clientList.erase(this->_clientFDs[i].fd);
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						delete client;
						break;
					default:
						std::vector<std::string>	vec = getVector(buffer);
						try
						{
							Command	cmd(vec, client, i);
						}
						catch (std::exception& e)
						{
							// Needs to do something else in case it failes to send
							if (selfClientSend(e.what(), this->_clientFDs[i].fd) < 0) std::cout << "failed to send" << std::endl;
						}
						break ;
				}
			}
		}
	}
};

void	server::setServerIp(const std::string& ip) { _serverIp = ip; }

std::string&	server::getServerIp()  { return _serverIp; }

void	server::setHostname(const std::string& hostname) { _hostname = hostname; }

std::string&	server::getHostname()  { return _hostname; }

void	server::setCreationTime(const std::string& timestamp) { _creationTime = timestamp; }

std::string&	server::getCreationTime()  { return _creationTime; };

bool	server::channelExists(const std::string& channelName){ return (channelList.find(channelName) != channelList.end()); }

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

void	server::addClient(Client *client) { _clientList[client->getFd()] = client; }

Client* server::getClientByFd(int fd)
{
	std::map<int, Client*>::iterator	 it = _clientList.find(fd);
    if (it != _clientList.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

bool	server::clientExists(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; ++itr) {
		if ((*itr).second->getNickName() == clientName) return true;
	}
	return (false);
}

std::map<int, Client*>	server::getClientList() { return _clientList; }
std::map<std::string, Channel*>	server::getChannelList() { return channelList; }