#pragma once

class Command
{
public:
	Command();
	virtual void execute() const = 0;
	virtual ~Command();
};