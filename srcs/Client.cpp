#include "server.hpp"
#include "Client.hpp"

Client::Client(std::string& serverPassword, int fd): _nickName(""),_userName(""), _isRegistered(false), _isValidatedPassword(false), _serverPassword(serverPassword), _totalChannels(0), _socketFd(fd) {}

Client::~Client() { close(_socketFd); }

void Client::registerClient() 
{
	_isValidatedPassword = true;
	_isRegistered = true;
//	 if (password.length() >= 4)
//	 {
//   } else {
//	 std::cerr << "Error: Password must be at least 6 characters long." << std::endl;
//   }
}  // Mark Client as registered
bool 					Client::getIsregistered() const { return _isRegistered; }
void					Client::setIsregistered() { _isRegistered = true; }
const std::string&		Client::getNickName() const{ return Client::_nickName;}
void					Client::setNickName(const std::string& newNickname){ _nickName = newNickname; }
const std::string&		Client::getUserName() const{ return Client::_userName;}
void					Client::setUserName(const std::string& newNickname){ _userName = newNickname; }
const std::string&		Client::getRealUserName() const{ return Client::_realUserName;}
void					Client::setRealUserName(const std::string& newNickname){ _realUserName = newNickname; }
const std::string&		Client::getHostname() const { return _hostname; };
void					Client::setHostname(const std::string& newHostname) { _hostname = newHostname; };
bool					Client::getIsValidatedPassword() const { return _isValidatedPassword; }
void					Client::setIsValidatePassword() { _isValidatedPassword = true; }
std::string				Client::getIdenClient() const{return (_nickName + "!" + _userName + "@" + _hostname);}
int						Client::getSocketFd() const {return _socketFd; }
const std::string&		Client::getServerPassword() const { return _serverPassword; }
void					Client::incrementTotalChannels() { _totalChannels++; }
int						Client::getFd() const { return _socketFd; }
int						Client::getTotalChannels() const { return _totalChannels; }
std::vector<Channel*>	Client::getChannelList() const { return _channelList; }
void					Client::addChannelToChannelList(Channel *channel) { _channelList.push_back(channel); }
std::string&			Client::getMessage() { return _message; }
