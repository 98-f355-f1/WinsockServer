#include <iostream>
#include <string>
#include "TCPListener.h"
#include "Quotd.h"

using namespace std;

void ListenerMsgReceived(TCPListener *listener, SOCKET clientSock, string message);

int main(int argc, char **argv)
{
	Quotd quotes("wisdomquotes.txt");

	cout << quotes.getRandomQuote() << endl;

	TCPListener server("127.0.0.1", 55000, ListenerMsgReceived);

	if (server.Init()) {
		server.Run();
	}

	server.Cleanup();

	system("pause");
	return (EXIT_SUCCESS);
}

void ListenerMsgReceived(TCPListener *listener, SOCKET clientSock, string message)
{
	listener->Send(clientSock, message);
}
