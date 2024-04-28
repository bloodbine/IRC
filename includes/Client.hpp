#pragma once

#include <iostream>
#include <vector>
#include "Channel.hpp"

class Channel;

class Client
{
private:
    /* data */
    std::string _nickName;
    std::string _userName;
    std::string _realUserName;
    bool _isRegistered; // Flag to track registration status
    bool _isValidatedPassword;
    std::string _serverPassword;
    std::vector<Channel*>   _channelList;
    int                _totalChannels;
    int _socketFd;
public:
    Client(std::string& serverPassword, int fd);
    ~Client();
    void Register();
    bool GetIsRegistered() const;
    const std::string& GetNickName() const;
    const std::string& GetUserName() const;
    const std::string& GetRealUserName() const;
    int     getScoketFd() const;
    const std::string& getServerPassword() const;
    void setNickName(const std::string& newNickname);
    void setUserName(const std::string& newClientname);
    void setRealUserName(const std::string& newClientname);
    bool getIsValidatedPassword() const;
    void setIsValidatePassword();
    void setIsRegistered();
    std::string GetIdenClient() const;
    int         getFd() const;
    int         getTotalChannels() const;
    void        incrementTotalChannels();
    // to implement
    std::vector<Channel*> getChannelList() const;
    void                  addChannelToChannelList(Channel *channel);
};

