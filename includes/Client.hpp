#pragma once

#include <iostream>


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
public:
    Client(std::string& serverPassword);
    void Register();
    bool GetIsRegistered() const;
    const std::string& GetNickName() const;
    const std::string& GetUserName() const;
    const std::string& GetRealUserName() const;
    const std::string& getServerPassword() const;
    void setNickName(const std::string& newNickname);
    void setUserName(const std::string& newClientname);
    void setRealUserName(const std::string& newClientname);
    bool getIsValidatedPassword() const;
    void setIsValidatePassword();
    void setIsRegistered();
    std::string GetIdenClient() const;
    ~Client();
};

