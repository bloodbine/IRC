#include "Client.hpp"

Client::Client(/* args */): _nickName(""),_userName(""), _isRegistered(false)
{}

Client::~Client()
{}

void Client::Register() { _isRegistered = true; }  // Mark Client as registered
bool Client::GetIsRegistered() const { return _isRegistered; }
const std::string& Client::GetNickName() const{ return Client::_nickName;}
const std::string& Client::GetUserName() const{ return Client::_userName;}
std::string Client::GetIdenClient() const{return (_nickName + "!" +_userName + "@");}
void Client::setNickName(const std::string& newNickname){ _nickName = newNickname;}
void Client::setUserName(const std::string& newNickname){_userName = newNickname;}
bool Client::getIsValidatedPassword() const { return _isValidatedPassword; }
void Client::setIsValidatePassword() { _isValidatedPassword = true; }