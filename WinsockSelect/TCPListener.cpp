#include "..\WinsockListener\TCPListener.h"

TCPListener::TCPListener(std::string ipAddress, WORD port, MessageRcvdHandler msgRcvdHandler)
{
}

TCPListener::~TCPListener()
{
}

void TCPListener::Send(SOCKET clientSock, std::string msg)
{
}

bool TCPListener::Init()
{
	return false;
}

void TCPListener::Run()
{
}

SOCKET TCPListener::CreateSocket()
{
	return SOCKET();
}

SOCKET TCPListener::WaitForConnection()
{
	return SOCKET();
}
