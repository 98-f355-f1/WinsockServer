#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <cstdlib>
#include <sstream>

//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(int argc, char **argv)
{
	// Initialze winsock
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	SOCKET listenSocket;
	SOCKET clientSocket;

	int iResult;

	/*
	Initialize Winsock, the use of WS2_32.dll, MAKEWORD(2,2) parameter
	of WSAStartup makes	a request for version 2.2 of Winsock on the system
	*/
	if ((iResult = WSAStartup(version, &wsaData)) != 0) {
		cout << "WsaStartUp failed to initialize: " << iResult << endl;
		WSACleanup();
		return(EXIT_FAILURE);
	}

	// Create a socket
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): %ld" << std::endl;
		return (EXIT_FAILURE);
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	/*
	Setup the TCP listening socket
	*/
	iResult = bind(listenSocket, (sockaddr*)&hint, sizeof(hint));
	if (iResult == SOCKET_ERROR)
	{
		cout << "Bind to SOCKET failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return(EXIT_FAILURE);
	}

	// Tell Winsock the socket is for listening 
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "Listen SOCKET failed: " << WSAGetLastError() << endl;
		closesocket(listenSocket);
		WSACleanup();
		return(EXIT_FAILURE);
	}

	// Create the master file descriptor set and zero it
	fd_set masterFD;
	FD_ZERO(&masterFD);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(listenSocket, &masterFD);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

	while (running)
	{
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages. 

		// E.g. You have a server and it's master file descriptor set contains 5 items;
		// the listening socket and four clients. When you pass this set into select(), 
		// only the sockets that are interacting with the server are returned. Let's say
		// only one client is sending a message at that time. The contents of 'copy' will
		// be one socket. You will have LOST all the other sockets.

		// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

		fd_set copyFD = masterFD;

		// See who's talking to us
		int socketCount = select(0, &copyFD, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			SOCKET sock = copyFD.fd_array[i];

			// Is it an inbound communication?
			if (sock == listenSocket)
			{
				// Accept a new connection
				clientSocket = accept(listenSocket, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(clientSocket, &masterFD);

				// Send a welcome message to the connected client
				string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
				send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &masterFD);
				}
				else
				{
					// Check to see if it's a command. \quit kills the server
					if (buf[0] == '\\')
					{
						// Is the command quit? 
						string cmd = string(buf, bytesIn);
						if (cmd == "\\quit")
						{
							running = false;
							break;
						}

						// Unknown command
						continue;
					}

					// Send message to other clients, and definiately NOT the listening socket
					for (size_t i = 0; i < masterFD.fd_count; i++)
					{
						SOCKET outSock = masterFD.fd_array[i];
						if (outSock != listenSocket && outSock != sock)
						{
							ostringstream ss;
							// place to add vector or unordered_map of 
							// nicknames (NICK) in IRC parlance
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listenSocket, &masterFD);
	closesocket(listenSocket);

	// Message to let users know what's happening.
	string msg = "Server is shutting down. Goodbye\r\n";

	while (masterFD.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = masterFD.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &masterFD);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
}