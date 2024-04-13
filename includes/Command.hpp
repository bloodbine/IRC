#pragma once

class server;
class Client;

class Command
{
public:
	Command();
	virtual char* execute() const = 0;
	virtual ~Command();
};