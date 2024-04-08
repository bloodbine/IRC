#pragma once

#include <iostream>


class Client
{
private:
    /* data */
    std::string _nickName;
    std::string _userName;
    bool _isRegistered; // Flag to track registration status
public:
    Client(/* args */);
    void Register();
    bool GetIsRegistered() const;
    const std::string& GetNickName() const;
    const std::string& GetUserName() const;
    void setNickName(const std::string& newNickname);
    void setUserName(const std::string& newClientname);
    std::string GetIdenClient() const;
    ~Client();
};

