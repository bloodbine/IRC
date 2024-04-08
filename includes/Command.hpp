#pragma once

class server;
class Client;

class Command
{
public:
	Command();
	virtual char* execute(server& server, Client& client) const = 0;
	virtual ~Command();
};