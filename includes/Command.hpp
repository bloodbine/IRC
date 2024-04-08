#pragma once

class server;

class Command
{
public:
	Command();
	virtual char* execute(server& Server) const = 0;
	virtual ~Command();
};