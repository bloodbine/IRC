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
};

server::~server() { close(this->_socketfd); }

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

int	server::customSend(char *tmp, int i, bool failedToSendMsg, std::vector<std::string> vec) const
{
	int	toSendFd;
	int	sendStatus;
	if (failedToSendMsg)
	{
		toSendFd = this->_clientFDs[i].fd;
		sendStatus = send(toSendFd, tmp, std::strlen(tmp), 0);
		return (sendStatus);
	}
	else if (validNick(vec[1]))
	{
		toSendFd = server::getClientFdByName(vec[1]);
		sendStatus = send(toSendFd, tmp, std::strlen(tmp), 0);
		return (sendStatus);
	}
	else if (vec[0] == "QUIT")
	{
		std::cout << "You called QUIT!\n";
		Client *client = this->_clientList[this->_clientFDs[i].fd];
		std::cout << "This is the name of the client " << client->GetNickName() << std::endl;
		std::vector<Channel*>	channelList = client->getChannelList();
		std::vector<Channel*>::iterator	tmpChannel = channelList.begin();
		std::vector<Channel*>::iterator	end = channelList.end();
		std::cout << "The client is member of the next channels: " << std::endl;
		for (; tmpChannel != end; ++tmpChannel)
		{
			std::cout << (*tmpChannel)->getName() << std::endl;
			std::string reasson = "no reasson";
			if (vec.size() > 1)
			{
				reasson = vec[1];
				for (size_t i = 2; i < vec.size(); i++) reasson += " " + vec[i];
			}
			// std::cout << ">>>>>>>" << std::endl;
			std::string out = ":127.0.0.1 " + client->GetNickName() + " leaves the channel [" + (*tmpChannel)->getName() + "] because " + reasson + "\n";
			char *tmp2 = strdup(out.c_str());
			Channel *channel = server::getChannelByName((*tmpChannel)->getName());
			std::map<std::string, Client*>	memberList = channel->getMemberList();
			// std::cout << ">>>>>>>" << std::endl;
			sendStatus = 0;
			std::map<std::string, Client*>::iterator itr = memberList.begin();
			std::map<std::string, Client*>::iterator end = memberList.end();
			for (; itr != end; ++itr)
			{
				toSendFd = (*itr).second->getFd();
				sendStatus = send(toSendFd, tmp2, std::strlen(tmp2), 0);
			}
			delete tmp2;
		}
	}
	else
	{
		Channel *channel = server::getChannelByName(vec[1]);
		std::map<std::string, Client*>	memberList = channel->getMemberList();
		std::map<std::string, Client*>::iterator itr = memberList.begin();
		std::map<std::string, Client*>::iterator end = memberList.end();
		for (; itr != end; ++itr)
		{
			toSendFd = (*itr).second->getFd();
			sendStatus = send(toSendFd, tmp, std::strlen(tmp), 0);
		}
	}
	return (sendStatus);
}

int	server::runNormalCommand(std::vector<std::string>& vec, int i, bool failedToSendMsg)
{
	char *tmp = getExecuteOut(this->_clientList[this->_clientFDs[i].fd], vec, &failedToSendMsg);
	customSend(tmp, i, failedToSendMsg, vec);
	delete tmp;
	return 0;
}

int							server::getClientFdByName(const std::string& clientName) const
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; itr++) {
		if ((*itr).second->GetNickName() == clientName) return (*itr).first;
	}
	return -1;
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
				char buffer[1024];
				bzero(buffer, sizeof(buffer));
				int bytesRead = recv(this->_clientFDs[i].fd, buffer, 1024, 0);
				switch(bytesRead)
				{
					case -1:
						std::cerr << "Client " << this->_clientFDs[i].fd << " error: ";
						std::cerr << errno << " ";
						perror("recv");
						this->_clientList.erase(this->_clientFDs[i].fd);
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						break;
					case 0:
						std::cout << "Client " << this->_clientFDs[i].fd << " disconnected" << std::endl;
						close(this->_clientFDs[i].fd);
						this->_clientList.erase(this->_clientFDs[i].fd);
						this->_clientFDs.erase(this->_clientFDs.begin() + i);
						break;
					default:
						std::cout << "Recieved message from Client " << this->_clientFDs[i].fd << std::endl;
						std::cout << std::string(buffer);
						std::vector<std::string> vec = getVector(buffer);
						if (vec.size() > 0 && (vec[0] == "PRIVMSG" || 
							vec[0] == "JOIN" || vec[0] == "PART" || vec[0] == "QUIT") ){
							runNormalCommand(vec, i, false);
							if (vec[0] == "QUIT")
							{
								std::cout << "Client " << this->_clientFDs[i].fd << " disconnected" << std::endl;
								close(this->_clientFDs[i].fd);
								this->_clientList.erase(this->_clientFDs[i].fd);
								this->_clientFDs.erase(this->_clientFDs.begin() + i);
							}
							break;
						}
						else
						{
							runNormalCommand(vec, i, true);
							break;
						}
				}
				this->_clientFDs[i].revents = 0;
			}
		}
	}
};

void	server::setServerIp(const std::string& ip) { _serverIp = ip; }

const std::string&	server::getServerIp() const { return _serverIp; }

bool	server::channelExists(const std::string& channelName) { return (channelList.find(channelName) != channelList.end()); }

void	server::addChannel(Channel *channel) { channelList[channel->getName()] = channel; }

Channel* server::getChannelByName(const std::string& channelName) { return channelList[channelName]; }

void	server::addClient(Client *client) { _clientList[client->getFd()] = client; }

Client* server::getClientByFd(int fd) { return _clientList[fd]; }

bool	server::clientExists(const std::string& clientName)
{
	std::map<int, Client*>::iterator itr = _clientList.begin();
	std::map<int, Client*>::iterator end = _clientList.end();
	for (; itr != end; ++itr) {
		if ((*itr).second->GetNickName() == clientName) return true;
	}
	return (false);
}
