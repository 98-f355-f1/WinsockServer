#pragma once

#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

// forward declaration of class
class TCPListener;

// Callback to data received
typedef void(*MessageRcvdHandler)(TCPListener *listener, SOCKET sockID, std::string msg);

class TCPListener
{

public:
	TCPListener(std::string ipAddress, WORD port, MessageRcvdHandler msgRcvdHandler);
	~TCPListener();

	// send a message to client
	void Send(SOCKET clientSock, std::string msg);
	bool Init();
	void Run();
	void Cleanup();

private:
	SOCKET CreateSocket();
	SOCKET WaitForConnection(SOCKET listenSocket);

	std::string				ipAddress;
	WORD					port;
	MessageRcvdHandler		messageReceived;
};