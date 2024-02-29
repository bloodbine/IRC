#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

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

std::vector<std::string>	split(const std::string& text);
int							isValidCmd(const std::string& text);
