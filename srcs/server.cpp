#include "server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <fcntl.h>
#include <utility>

std::multimap<int, struct message>		server::messageList;
std::map<std::string, Channel*>			server::channelList;
std::map<int, Client*>					server::clientList;
std::vector<pollfd>						server::clientFDs;
std::string								server::_hostname;
std::string								server::_serverIp;
std::string								server::_creationTime;
bool									server::_finish;

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
		displayInstructions();
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
			Client *client = clientList[clientFDs[i].fd];
			if (client != NULL)
			{
				char buffer[1024];
				bzero(buffer, sizeof(buffer));
				std::vector<Channel*> clientChannelList = client->getChannelList();
				if (clientFDs[i].revents & POLLIN)
				{
					int bytesRead = recv(clientFDs[i].fd, buffer, 1024, 0);
					if (bytesRead <= 0)
					{
						std::cout << "Client " << clientFDs[i].fd << " disconnected" << std::endl;
						if (clientChannelList.size() > 0)
						{
							std::vector<Channel*>::iterator	tmpChannel = clientChannelList.begin();
							std::vector<Channel*>::iterator	end = clientChannelList.end();
							for (; tmpChannel != end; ++tmpChannel)
							{
								if((*tmpChannel) != NULL)
								{
									std::string stringToSend = ":" + client->getIdenClient() + " PART " + (*tmpChannel)->getName() + " :Client disconnected\r\n";
									sendToChannel(stringToSend, (*tmpChannel)->getName(), client->getNickName());
									(*tmpChannel)->removeOperator(*client);
									(*tmpChannel)->removeUser(*client);
								}
							}
						}
						clearClientMessages(clientFDs[i].fd);
						close(clientFDs[i].fd);
						clientList.erase(clientFDs[i].fd);
						clientFDs.erase(clientFDs.begin() + i);
						delete client;
					}
					else
					{
						std::string& tmp = client->getMessage();
						tmp += buffer;
						if (tmp.find("\n") != std::string::npos || tmp.find("\r\n") != std::string::npos)
						{
							std::cout << "[DEBUG] Message In " << clientFDs[i].fd <<  ": " << tmp;
							std::vector<std::string> vec = getVector((char *)(tmp.c_str()));
							tmp.clear();
							try
								{if (vec.size() > 0) Command cmd(vec, client);}
							catch (std::exception& e)
								{selfClientSend(e.what(), clientFDs[i].fd, NOFLAG);}
						}
					}
				}
				if (clientFDs[i].revents & POLLOUT && messageList.size() != 0)
				{
					std::multimap<int, struct message>::iterator message = messageList.equal_range(clientFDs[i].fd).first;
					if (message != server::messageList.end())
					{
						std::cout << "[DEBUG] Message Out " << clientFDs[i].fd << ": "  << message->second.flag << " " << message->second.data;
						int senderr = 0;
						std::vector<pollfd>::iterator fdStart = clientFDs.begin();
						std::vector<pollfd>::iterator fdEnd = clientFDs.end();
						for (; fdStart != fdEnd; fdStart++)
						{
							if ((*fdStart).fd == message->first)
							{
								senderr = send(message->first, (message->second.data).c_str(), (message->second.data).length(), 0);
								break;
							}
						}
						if (senderr == -1)
							perror("send");
						else if (senderr > 0)
						{
							if (message->second.flag == PARTING)
							{
								size_t chanNameStart = message->second.data.find("#");
								size_t chanNameEnd = message->second.data.find(" ", chanNameStart);
								std::string channelName = message->second.data.substr(chanNameStart, chanNameEnd - chanNameStart);
								Channel* channel = getChannelByName(channelName);
								if (channel != NULL)
								{
									Client* client = getClientByFd(clientFDs[i].fd);
									channel->removeUser(*client);
									channel->removeOperator(*client);
									if (channel->getOperatorList().size() == 0 && channel->getMemberList().size() != 0)
									{
										std::string stringToSend = ":" + server::getHostname() + " MODE " + channel->getName() + " +o " + (*channel->getMemberList().begin()).second->getNickName() + "\r\n";
										selfClientSend(stringToSend, (*channel->getMemberList().begin()).second->getFd(), NOFLAG);
										channel->addOperator((*channel->getMemberList().begin()).second);
									}
									if (channel->getMemberList().size() == 0)
									{
										delete channel;
										channel = NULL;
										channelList.erase(channelName);
									}
								}
							}
							if (message->second.flag == QUITING)
							{
								std::cout << "Client " << message->first << " disconnected" << std::endl;
								delete getClientByFd(message->first);
								clientList.erase(message->first);
								clientFDs.erase(clientFDs.begin() + i);
							}
							messageList.erase(message);
						}
					}
				}
				clientFDs[i].revents = 0;
			}
		}
	}
	std::map<std::string, Channel*>					channelList = server::getChannelList();
	std::map<std::string, Channel*>::iterator		itr1 = channelList.begin();
	std::map<std::string, Channel*>::iterator		end1 = channelList.end();
	for (; itr1 != end1; ++itr1) delete (*itr1).second;

	std::map<int, Client*>					clientList = server::getClientList();
	std::map<int, Client*>::iterator		itr2 = clientList.begin();
	std::map<int, Client*>::iterator		end2 = clientList.end();
	for (; itr2 != end2; ++itr2) delete (*itr2).second;
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
		std::map<std::string, Channel*>::iterator it = channelList.find(channelName);
		if ((*it).second != NULL && it != channelList.end()) {
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

void server::displayInstructions()
{
	std::cout << "Server Information:" << std::endl;
	std::cout << "Host: " << _hostname << std::endl;
	std::cout << "IP: " << _serverIp << std::endl;
	std::cout << "Port: " << _port << std::endl;
	std::cout << "Pass: " << _pass << std::endl << std::endl;

	std::cout << "Login Process: (ignore \"/\" if on netcat)" << std::endl;
	std::cout << "\t/PASS <pass>" << std::endl;
	std::cout << "\t/NICK <nickname>" << std::endl;
	std::cout << "\t/USER <username> 0 * :<real username>" << std::endl << std::endl;

	std::cout << "Commands: (ignore \"/\" if on netcat)" << std::endl;
	std::cout << "\t/JOIN #<channel>" << std::endl;
	std::cout << "\t\t-Join or Create channel" << std::endl << std::endl;
	std::cout << "\t/PART #<channel>" << std::endl;
	std::cout << "\t\t-Leave Channel" << std::endl << std::endl;
	std::cout << "\t/TOPIC #<channel> (<topic>)" << std::endl;
	std::cout << "\t\t-Display or Change Channel topic" << std::endl << std::endl;
	std::cout << "\t/PRIVMSG <targetuser>/#<channel> <message>" << std::endl;
	std::cout << "\t\t-Send message to User or Channel" << std::endl << std::endl;
	std::cout << "\t/INVITE <targetuser> #<channel>" << std::endl;
	std::cout << "\t\t-Invite user to join Channel" << std::endl << std::endl;
	std::cout << "\t/KICK #<channel> <targetuser>" << std::endl;
	std::cout << "\t\t-Remove user from channel" << std::endl << std::endl;
	std::cout << "\t/MODE #<channel> +/-<mode> (<parameter>)" << std::endl;
	std::cout << "\t\t-Change Channel Mode (i/k/t/o/l)" << std::endl << std::endl;
	std::cout << "\t/QUIT (<reason>)" << std::endl;
	std::cout << "\t\t-Leave Server" << std::endl;
}

void server::setFinished(bool status) { _finish = status; }

std::map<int, Client*>&				server::getClientList() { return clientList; }
std::map<std::string, Channel*>&	server::getChannelList() { return channelList; }
std::multimap<int, struct message>&	server::getMessageList() { return messageList; }
