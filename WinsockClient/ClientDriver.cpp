#include <Winsock2.h>
#include "Client.h"

int main(int argc, char **argv)
{
	using namespace std;

	WSADATA wsaData;
	bool running = true;
	int iResult, c = 0, count = 0;
	const char *sendBuf = "This a fucking test";
	char recvBuf[BUFFER_SIZE];
	char clientBuf[BUFFER_SIZE];

	struct addrinfo *result, *ptr, hints;

	SOCKET serverSocket = INVALID_SOCKET;

	/*
	TODO: Get arguments and get options for different choices
	*/
	// Validate the parameters
	if (argc != 2) {
		cout << "Usage: %s <server-name>" << argv[0] << endl;
		return(EXIT_FAILURE);
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed with error: %d\n" << iResult << endl;
		return(EXIT_FAILURE);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		cout << "Getaddrinfo failed: " << iResult << endl;
		WSACleanup();
		return(EXIT_FAILURE);
	}

	/*
	Attempt to connect to the first address returned by
	the call to getaddrinfo
	*/
	ptr = result;

	/*
	Attemp to connect to the Server SOCKET until one succeeds
	*/
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		/*
		Create a SOCKET for connecting to server
		*/
		serverSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (serverSocket == INVALID_SOCKET)
		{
			cout << "Server SOCKET failed: " << WSAGetLastError() << endl;
			freeaddrinfo(result);
			WSACleanup();
			return(EXIT_FAILURE);
		}

		// Connect to the Server SOCKET
		iResult = connect(serverSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			cout << "Server CONNECT failed: " << iResult << endl;
			closesocket(serverSocket);
			serverSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect to Server Socket" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return(EXIT_FAILURE);
	}

	while (true)
	{		
		ZeroMemory(clientBuf, BUFFER_SIZE);
		ZeroMemory(recvBuf, BUFFER_SIZE);

		iResult = recv(serverSocket, recvBuf, BUFFER_SIZE, 0);
		if (iResult == SOCKET_ERROR)
		{
			cout << "Receive failed: " << iResult << endl;
		}

		cout << recvBuf << endl;

		//getInput(clientBuf, c, BUFFER_SIZE);

		//if ((fgets(clientBuf, BUFFER_SIZE, stdin)) != NULL)
		//	if (clientBuf[strlen(clientBuf) - 1] == '\n')
		//		clientBuf[strlen(clientBuf) - 1] = '\0';

		cin.getline(clientBuf, BUFFER_SIZE);

		if ((strncmp(clientBuf, "quit", 4) == 0) ||
			(strncmp(clientBuf, "exit", 4) == 0))
		{
			send(serverSocket, clientBuf, (int)strlen(clientBuf), 0);
			running = false;
			Sleep(1);
			break;
		}

		// Send initial buffer
		iResult = send(serverSocket, clientBuf, (int)strlen(clientBuf), 0);
		if (iResult == SOCKET_ERROR)
		{
			cout << "Send failed: " << iResult << endl;
			closesocket(serverSocket);
			WSACleanup();
			return(EXIT_FAILURE);
		}

		cout << "Bytes sent: " << iResult << endl;
	}

	/*
	Receive data until the server closes the connection
	*/
	do {
		iResult = recv(serverSocket, recvBuf, BUFFER_SIZE, 0);
		if (iResult > 0)
			cout << "Bytes recieved: " << iResult << endl;
		else if (iResult == 0)
			cout << "Connection has closed" << endl;
		else
			cout << "Recv failed: " << WSAGetLastError() << endl;
	} while (iResult > 0);

	/*
	Shutdown the connection for sending since no more data will be sent
	the client can still use the ConnectSocket for receiving data
	*/
	iResult = shutdown(serverSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Shutdown failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return(EXIT_FAILURE);
	}

	// Cleanup
	closesocket(serverSocket);
	WSACleanup();

	return(EXIT_SUCCESS);
}