#include "Server.h"

constexpr auto BUF_SIZE = 4096;
typedef void (CHATTER::* pf)(std::string);
volatile bool running;
using namespace std;

ChatterDB chatterDB;

/*
Development of the proper C++ Classes
*/
Server::Server(CommandRcvdHandler cmdRcvdHndlr) : commandRcvdHandler(cmdRcvdHndlr)
{
	port = "25000";
}

Server::Server(const char *portNum, CommandRcvdHandler cmdRcvdHndlr) : port(portNum), commandRcvdHandler(cmdRcvdHndlr)
{
}

Server::Server(UINT portNum)
{	
	string s = to_string(portNum);
	const char *p = s.c_str();
	port = p;
};

int Server::init()
{
	int iResult;
	
	#ifdef _WIN32
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		//handle error
		// WSAGetLastError();
		cout << "WsaStartUp failed to initialize: " << iResult << endl;
		WSACleanup();
		return (_EXIT_FAILURE);
	}
	#endif

	/*
	Initialize the struct addrinfo
	*/
	#ifdef _WIN32
	ZeroMemory(&hints, sizeof(hints));
	#else
	memset(&hints, sizeof(hints));
	#endif

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	/*
	Resolve the server address and port
	*/
	iResult = getaddrinfo(nullptr, port, &hints, &result);
	if (iResult != 0) {
		cout << "Getaddrinfo failed with error: " << iResult << endl;

		#ifdef _WIN32
		WSACleanup();
		#endif

		return (_EXIT_FAILURE);
	}
	 
	/*
	Create a SOCKET for the server to listen for client connections
	*/
	listenSckt = createSocket();
	if (listenSckt == INVALID_SOCKET)
	{
		cout << "Error at socket(): %ld" << std::endl;
		freeaddrinfo(result);
		return (_EXIT_FAILURE);
	}

	if ((iResult = bindSocket()) == SOCKET_ERROR)
	{
		cout << "Bind to SOCKET failed: " << WSAGetLastError() << endl;

		#ifdef _WIN32
		freeaddrinfo(result);
		WSACleanup();
		#endif

		return (_EXIT_FAILURE);
	}

	// getaddrinfo no longer needed, free the space
	#ifdef _WIN32
	freeaddrinfo(result);
	#endif

	return (_EXIT_SUCCESS);
}

void Server::run()
{
	DWORD threadId = 1;

	/*
	Listen on the TCP listening socket
	*/
	if ((iResult = listenSocket()) == SOCKET_ERROR)
	{
		cout << "Listen SOCKET failed: " << WSAGetLastError() << endl;
		#ifdef _WIN32
		freeaddrinfo(result);
		WSACleanup();
		#endif
		return; // exit??
	}

	/*
	Server print statements for fun!!
	*/
	server_printouts(port);

	running = true;
	while (running)
	{
		/*
		Accept a client socket
		*/
		int clientSize = sizeof(client);
		clientSckt = acceptSocket();
		if (clientSckt == INVALID_SOCKET)
		{			
			#ifdef _WIN32
			cout << "accept failed: " << WSAGetLastError() << endl;
			closesocket(listenSckt);
			WSACleanup();
			#endif

			running = false;
			break; // exit??
		}

		// Get client information: Tuple(clientHostName, socket, port)
		Tuple clientInfo;
		clientInfo = getClientInfo(clientSckt, clientSize);

		SOCKET client = clientSckt;

		// Create a shared pointer to a new CHATTER with the 3 pieces of client information
		auto chatter = make_shared<CHATTER>(get<1>(clientInfo), get<2>(clientInfo), get<0>(clientInfo));
			
		// Push the information into the Chatter map
		chatterDB.insert(std::pair<SOCKET, shared_ptr<CHATTER>>(get<1>(clientInfo), chatter));

		// A thread for the welcome message
		std::thread t1 = thread(&Server::welcomeChatter, this, chatter);
		// OR std::thread t{ &welcomeChatter, chatter }; 	
		t1.detach();

		// Handle client
		std::thread t2 = thread(&Server::handleClient, this, chatter, threadId++);
		t2.detach();
	}
}

void Server::welcomeChatter(shared_ptr<CHATTER> c)
{
	bool finished = false;

	// Send a welcome message to the connected client
	string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
	commandRcvdHandler(this, c->getSocket(), welcomeMsg);
}

int Server::handleClient(shared_ptr<CHATTER> c, DWORD threadId)
{
	cout << "Serviced by pthread #" << threadId << endl;

	/*
	While loop: accept and echo back information to client
	*/
	char recvBuf[BUFFER_SIZE];
	int iResult;
	int recvBufLen = BUFFER_SIZE;

	/*
	Receive until the server shuts down the connection
	*/
	do {

		// Zero out buffer, to start each time fresh
		ZeroMemory(recvBuf, sizeof(recvBuf));

		iResult = recv(c->getSocket(), recvBuf, recvBufLen, 0);
		if (iResult > 0)
		{
			cout << "Bytes received: " << iResult << endl;
			print(recvBuf, iResult);

			if (calledExit(string(recvBuf)))
			{
				handleExit(c);
			}

			// first line of defense
			if (recvBuf[0] == '*')
			{	
				std::string newNick = std::string(recvBuf);
				newNick = newNick.substr(1, newNick.size() - 3);
				c->setNick(newNick);

				// Add the chatter to the list
				std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n"
					+ newNick + " has been successfully registered with the server.\r\n";
				commandRcvdHandler(this, c->getSocket(), welcomeMsg);
				continue;
			}
			
			if (recvBuf[0] == '/')
			{
				commandRcvdHandler(this, c->getSocket(), string(recvBuf));
				continue;
			}

			// Broadcast to all chatters
			for (auto element : chatterDB)
			{
				std::cout << element.first << " :: " << element.second << std::endl;

				SOCKET temp = element.first;
				if (c->getSocket() != temp)
				{
					std::string msg = c->getNick() + " wrote: " + recvBuf + "\r\n";
					commandRcvdHandler(this, temp, msg);
				}
			}
			//std::unordered_map<SOCKET, shared_ptr<CHATTER>>::const_iterator iter;
			//for (iter = chatterDB.begin(); iter != chatterDB.end(); iter++)
			//{
			//	SOCKET temp = iter->first;
			//	if (c->getSocket() != temp) {
			//		std::string msg = c->getNick() + " wrote: " + recvBuf + "\r";
			//		commandRcvdHandler(this, temp, msg);
			//	}
			//}
		}
		
		if (iResult == 0)
		{
			cout << "Client connection closing. . ." << endl;
			return closeClientConnection(c->getSocket());
		}
		
		if (iResult == SOCKET_ERROR)
		{
			cout << "Recv failed: " << WSAGetLastError() << endl;
			closesocket(c->getSocket());
			WSACleanup();
			return closeClientConnection(c->getSocket());
		}

	} while (true);

	return 1;
}

Tuple Server::getClientInfo(SOCKET sock, int clsize)
{
	char clientName[NI_MAXHOST];
	char servicePort[NI_MAXSERV];

	#ifdef _WIN32
	ZeroMemory(clientName, NI_MAXHOST); // memset on Linux
	ZeroMemory(servicePort, NI_MAXSERV);
	#else
	memset(clientName, NI_MAXHOST); // memset on Linux
	memset(servicePort, NI_MAXSERV);
	#endif

	if (getnameinfo((sockaddr *)&client, clsize, clientName, NI_MAXHOST, servicePort, NI_MAXSERV, NULL) == 0)
	{
		cout << clientName << " connected on port " << servicePort << endl;
		Tuple triple(string(clientName), sock, (UINT)atoi(servicePort));
		return triple;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, clientName, NI_MAXHOST);
		cout << clientName << " connected on port " << ntohs(client.sin_port) << endl;
		Tuple triple(string(clientName), sock, (UINT)ntohs(client.sin_port));
		return triple;
	}
}

SOCKET Server::createSocket()
{
	/*
	Create a SOCKET for the server to listen for client connections
	*/
	return ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
}

int Server::bindSocket()
{
	/*
	Setup the TCP listening socket
	*/
	return ::bind(listenSckt, result->ai_addr, (int)result->ai_addrlen);
}

int Server::listenSocket()
{
	/*
	Listen on the TCP listening socket
	*/
	return ::listen(listenSckt, SOMAXCONN);
}

int Server::connectSocket()
{
	return 1;
}

int Server::acceptSocket()
{
	/*
	Accept a client socket
	*/
	int clientSize = sizeof(client);
	return ::accept(listenSckt, (sockaddr *)&client, &clientSize);
}

int Server::sendMsg(SOCKET clientSock, std::string msg)
{
	return send(clientSock, msg.c_str(), msg.size() + 1, 0);
}

bool Server::calledExit(std::string message)
{
	std::transform(message.begin(), message.end(), message.begin(), tolower);
	if ((strncmp(message.c_str(), "/quit", 5) == 0) ||
		(strncmp(message.c_str(), "/exit", 5) == 0))
	{
		return true;
	}
	return false;
}

int Server::handleExit(shared_ptr<CHATTER> c)
{
	cout << "Client: "
		<< c->getNick()
		<< " closed connection"
		<< endl;

	string msg = "Goodbye, " + c->getNick() + "\r\n";
	sendMsg(c->getSocket(), msg);
	Sleep(2000);
	return closeClientConnection(c->getSocket());
}

int Server::closeClientConnection(SOCKET clientSock)
{
	/*
	Shutdown the send half of the connection since no more data will be sent
	*/
	return shutdown(clientSock, SD_SEND);
}

char *strcopy(char *dest, const char *src, size_t size)
{
	size_t i;

	for (i = 0; i < size && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < size; i++)
		dest[i] = '\0';

	return dest;
}

void print(const char *text, int size)
{
	int i;
	cout << "[CLIENT] => ";
	for (i = 0; i < size; i++)
		cout << text[i];
	cout << endl;
}

int close_client_connection(int clientSock)
{
	/*
	Shutdown the send half of the connection since no more data will be sent
	*/
	return shutdown(clientSock, SD_SEND);
}

void shutdown_server(int clientSock)
{
	Sleep(1000);
	closesocket(clientSock);
	WSACleanup();
}

void server_printouts(const char *port)
{
	cout << "Initializing Server. . . " << endl;
	cout << "Accepting requests on port " << port << endl;
	cout << "Hello, let's get this party started" << endl;
}

void threadFailed()
{
	cout << "CreateThread failed: " << WSAGetLastError() << endl;
	//closesocket(srvr);
	//closesocket(clnt);
	//WSACleanup();
	return;
}
