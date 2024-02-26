#include "Privmsg.hpp"

Privmsg::Privmsg(const std::string& text) : _targetIsUser(false), _target("default"), _message("bad message")
{
	(void)text;
}
Privmsg::~Privmsg() {}

bool				Privmsg::getTargetIsUser() const { return _targetIsUser; }
const std::string&	Privmsg::getTarget() const { return _target; }
const std::string&	Privmsg::getMessage() const { return _message; }