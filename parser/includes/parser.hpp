#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "commands/commands.hpp"

/*
Colors
*/
#define RESET_COLOR "\033[0m"
#define BOLD_ON "\033[1m"
#define BOLD_OFF "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"

/*
CMD codes
*/
# define PRIVMSG 0
# define PASS 1
# define WHOIS 2
# define WHO 3
# define PING 4
# define CAP 5
# define PART 6
# define LIST 7
# define MODE 8
# define QUIT 9
# define JOIN 10
# define NICK 11
# define MOTD 12
# define TOPIC 13

void						printError(const std::string& msg);
std::vector<std::string>	split(const std::string& text);
int							isValidCmd(const std::string& text);
bool						isValidUserName(const std::string& name);
bool						isValidChannelName(const std::string& name);
bool						isValidModeCmd(const std::vector<std::string>& vec);
