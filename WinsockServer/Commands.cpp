#include "Server.h"

Commands::Commands(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	std::string line;

	if (file.is_open())
	{
		for (int i = 1; getline(file, line); i++)
		{
			commands[line] = i;
		}
	}
}

CmdMap Commands::getCommands()
{
	return commands;
}

bool Commands::compareCommand(std::string command)
{
	const char *c = command.c_str();

	for (CmdMap::iterator it = commands.begin(); it != commands.end(); ++it)
	{
		if (strncmp(it->first.c_str(), c, command.size()) == 0) {
			std::cout << "TRUE" << std::endl;
			return true;
		}
	}

	return false;
}

std::string Commands::getCommand(std::string command)
{
	const char *c = command.c_str();
	std::string found;

	for (CmdMap::iterator it = commands.begin(); it != commands.end(); ++it)
	{
		if (strncmp(it->first.c_str(), c, command.size()) == 0)
		{
			std::cout << "TRUE" << std::endl;
			return it->first;
		}
	}

	return NULL;
}
