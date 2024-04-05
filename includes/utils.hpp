#pragma once

#include "Command.hpp"
#include "commands/Cap.hpp"
#include <sstream>

std::vector<std::string> getVector(char *in);
Command	*getCommand(const std::vector<std::string>& vec);