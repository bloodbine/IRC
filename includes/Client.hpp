#pragma once

#include <iostream>
#include <vector>
#include "Channel.hpp"

class Channel;

class Client
{
	private:
		/* data */
		std::string				_nickName;
		std::string				_userName;
		std::string				_realUserName;
		std::string				_hostname;
		bool					_isRegistered; // Flag to track registration status
		bool					_isValidatedPassword;
		std::string				_serverPassword;
		std::vector<Channel*>	_channelList;
		int						_totalChannels;
		int 					_socketFd;
		int						_zeroReadCount;
		std::string				_message;
	public:
		Client(std::string& serverPassword, int fd);
		~Client();
		void					registerClient();
		bool					getIsregistered() const;
		void					setIsregistered();
		const std::string&		getNickName() const;
		void					setNickName(const std::string& newNickname);
		const std::string&		getUserName() const;
		void					setUserName(const std::string& newClientname);
		const std::string&		getRealUserName() const;
		void					setRealUserName(const std::string& newClientname);
		const std::string&		getHostname() const;
void							setHostname(const std::string& newHostname);
		int						getSocketFd() const;
		const std::string&		getServerPassword() const;
		bool					getIsValidatedPassword() const;
		void					setIsValidatePassword();
		void					incrementTotalChannels();
		int						getTotalChannels() const;
		std::string				getIdenClient() const;
		int						getFd() const;
		int&					getZeroReadCount();
		std::vector<Channel*>	getChannelList() const;
		void					addChannelToChannelList(Channel *channel);
		void					appendToMessage(char *buff);
		std::string&			getMessage();
};

