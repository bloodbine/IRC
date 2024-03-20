#include "parser.hpp"

Mode::Mode(const std::vector<std::string>& cmd) : _target(""), _mode(""), _optional("")
{
	if (isValidModeCmd(cmd) == false) throw std::invalid_argument("Invalid Mode syntax!");
	_target = cmd[1].substr(1);
	_mode = cmd[2];
	if (cmd.size() == 4) _optional = cmd[3];
}

Mode::~Mode() {}

const std::string&	Mode::getTarget() const { return _target; }
const std::string&	Mode::getMode() const { return _mode; }
const std::string&	Mode::getOptional() const { return _optional; }
