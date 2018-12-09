#include <iostream>
#include "TCPListener.h"

using namespace std;

#define BUFFERSIZE (4096)

TCPListener::TCPListener(std::string ipAddress, WORD port, MessageRcvdHandler msgRcvdHandler)
	: ipAddress(ipAddress), port(port), messageReceived(msgRcvdHandler)
{
}

TCPListener::~TCPListener()
{
	Cleanup();
}

void TCPListener::Send(SOCKET clientSock, std::string msg)
{
	send(clientSock, msg.c_str(), msg.size() + 1, 0);
}

bool TCPListener::Init()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	int wsInit = WSAStartup(version, &wsaData);
	if (wsInit != 0)
	{
		//handle error
		// WSAGetLastError();
		cout << "WsaStartUp failed to initialize: " << wsInit << endl;
		WSACleanup();
		return false;
	}

	return wsInit == 0;
}

void TCPListener::Run()
{
	char buffer[BUFFERSIZE];

	while (true)
	{
		SOCKET listeningSocket = CreateSocket();
		if (listeningSocket == INVALID_SOCKET)
		{
			break;
		}

		SOCKET clientSocket = WaitForConnection(listeningSocket);
		if (clientSocket != SOCKET_ERROR)
		{
			closesocket(listeningSocket);

			int bytesReceived = 0;
			do
			{
				ZeroMemory(buffer, BUFFERSIZE);
				bytesReceived = recv(clientSocket, buffer, BUFFERSIZE, NULL);
				if (messageReceived > 0)
				{
					if (messageReceived != NULL)
					{
						messageReceived(this, clientSocket, std::string(buffer, 0, bytesReceived));
					}
				}
			} while (bytesReceived > 0);

			closesocket(clientSocket);
		}
	}
}

void TCPListener::Cleanup()
{
	WSACleanup();
}

SOCKET TCPListener::CreateSocket()
{
	SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listeningSocket != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		int bindOK = bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));
		if (bindOK != SOCKET_ERROR)
		{
			int listenOK = listen(listeningSocket, SOMAXCONN);
			if (listenOK == SOCKET_ERROR) {
				return -1;
			}
		}
		else {
			return -1;
		}
	}

	return listeningSocket;
}

SOCKET TCPListener::WaitForConnection(SOCKET listener)
{
	return accept(listener, nullptr, nullptr);
}
