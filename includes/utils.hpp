#pragma once

#include "Command.hpp"
#include "commands/Cap.hpp"
#include "commands/Pass.hpp"
#include "commands/Nick.hpp"
#include "commands/User.hpp"
#include <sstream>

std::vector<std::string> getVector(char *in);
Command	*getCommand(const std::vector<std::string>& vec);
bool	isSpecialChar(char c);