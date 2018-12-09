#include "Server.h"
#include "CommandHandler.h"

int main(int argc, char **argv)
{
	using namespace Chat;

	/*
	Check arguments, set port or get default PORT
	*/
	if (argc == 2)
	{
		Server server(argv[1], ServerCommandHandler);
		if (server.init() != SOCKET_ERROR)
			server.run();
	}
	else
	{
		Server server(ServerCommandHandler);
		if (server.init() != SOCKET_ERROR)
			server.run();
	}

	return 0;
}