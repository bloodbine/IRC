#pragma once

class Command
{
public:
	Command();
	virtual char* execute() const = 0;
	virtual ~Command();
};