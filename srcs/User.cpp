#include "User.hpp"

User::User(/* args */): _nickName(""), _userName(""), _isRegistered(false)
{}

User::~User()
{}

void User::Register() { _isRegistered = true; }  // Mark user as registered
bool User::GetIsRegistered() const { return _isRegistered; }
const std::string& User::GetNickName() const{ return User::_nickName;}
const std::string& User::GetUserName() const{ return User::_userName;}
std::string User::GetIdenUser() const{return (_nickName + "!" + _userName + "@");}
void User::setNickName(const std::string& newNickname){ _nickName = newNickname;}
void User::setUserName(const std::string& newNickname){ _userName = newNickname;}
