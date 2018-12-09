#pragma once

#include "Server.h"

typedef	std::unordered_map<std::string, int> CmdMap;
typedef std::vector<std::string> Vector;

class Commands
{

public:
	Commands(std::string filename);

	bool compareCommand(std::string command);
	std::string getCommand(std::string command);
	CmdMap getCommands();

private:
	CmdMap commands;
	Vector vec;
};
