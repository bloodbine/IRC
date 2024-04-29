#pragma once

#include <string>

class server;
class Client;

class Command
{
public:
	Command();
	virtual std::string execute() const = 0;
	virtual ~Command();
};