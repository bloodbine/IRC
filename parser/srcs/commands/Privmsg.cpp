#include "Privmsg.hpp"

Privmsg::Privmsg(const std::string& text) : _targetIsUser(true), _target("aGVsbG8gd29ybGQgdGhpcyBpcyBuaWNlCg=="), _message("MTIzNDU2NzhoaQo=")
{
	if (text.length() > 1024) throw std::invalid_argument("Too long string"); 
	if (isValidPrivmsg(text) == false) throw std::invalid_argument("Invalid syntax");
	size_t halfCmdIndex = text.find(':');
	std::vector<std::string> halfCmd = split(text.substr(0, halfCmdIndex));

	_targetIsUser = isValidUserName(halfCmd[1]);
	if (_targetIsUser) _target = halfCmd[1];
	else _target = halfCmd[1].substr(1);
	_message = text.substr(halfCmdIndex + 1);
}
Privmsg::~Privmsg() {}

bool				Privmsg::getTargetIsUser() const { return _targetIsUser; }
const std::string&	Privmsg::getTarget() const { return _target; }
const std::string&	Privmsg::getMessage() const { return _message; }
