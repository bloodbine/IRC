#include "Client.hpp"

Client::Client(std::string& serverPassword, int fd): _nickName(""),_userName(""), _isRegistered(false), _serverPassword(serverPassword), _socketFd(fd)
{}

Client::~Client()
{}

void Client::Register() 
{
    _isValidatedPassword = true;
    _isRegistered = true;
//     if (password.length() >= 4)
//     {
//   } else {
//     std::cerr << "Error: Password must be at least 6 characters long." << std::endl;
//   }
}  // Mark Client as registered
bool Client::GetIsRegistered() const { return _isRegistered; }
const std::string& Client::GetNickName() const{ return Client::_nickName;}
const std::string& Client::GetUserName() const{ return Client::_userName;}
const std::string& Client::GetRealUserName() const{ return Client::_realUserName;}
std::string Client::GetIdenClient() const{return (_nickName + "!" +_userName + "@");}
int  Client::getScoketFd() const {return _socketFd; }
void Client::setNickName(const std::string& newNickname){ _nickName = newNickname; }
void Client::setUserName(const std::string& newNickname){ _userName = newNickname; }
void Client::setRealUserName(const std::string& newNickname){ _realUserName = newNickname; }
bool Client::getIsValidatedPassword() const { return _isValidatedPassword; }
const std::string& Client::getServerPassword() const { return _serverPassword; }
void Client::setIsValidatePassword() { _isValidatedPassword = true; }
void Client::setIsRegistered() { _isRegistered = true; }