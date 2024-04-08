#pragma once

#include <iostream>


class User
{
private:
    /* data */
    std::string _nickName;
    std::string _userName;
    bool _isRegistered; // Flag to track registration status
public:
    User(/* args */);
    void Register();
    bool GetIsRegistered() const;
    const std::string& GetNickName() const;
    const std::string& GetUserName() const;
    void setNickName(const std::string& newNickname);
    void setUserName(const std::string& newUsername);
    std::string GetIdenUser() const;
    ~User();
};

