#pragma once

class server;
class Client;

class Command
{
public:
	Command();
	virtual void execute() = 0;
	virtual int sendToClient() const = 0;
	virtual ~Command();
};