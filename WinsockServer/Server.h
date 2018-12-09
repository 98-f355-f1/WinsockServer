#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif
#include <thread>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <vector>
#include <variant>
#include <unordered_map>
#include "Quotd.h"
#include "Commands.h"
#include "Chatter.h"
#include "ChatRoom.h"

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

constexpr auto _EXIT_SUCCESS = (0);
constexpr auto _EXIT_FAILURE = (-1);
constexpr auto BUFFER_SIZE	= (512);

char *strcopy(char *, const char *, size_t);
void print(const char *, int size);
int close_client_connection(int);
void shutdown_server(int);
void server_printouts(const char*);
void threadFailed();

// start documenting
typedef std::unordered_map<SOCKET, std::shared_ptr<CHATTER>> ChatterDB;
typedef Chat::Chatroom Chatroom;
typedef std::unordered_map<int, std::string> ChatroomsDB;
typedef std::tuple<std::string, SOCKET, UINT> Tuple;

// Forward class Server
class Server;

// Callback to data received
typedef void(*CommandRcvdHandler)(Server *listener, SOCKET sockID, std::string msg);

// Callback to data received
typedef void(*ChatterHandler)(CHATTER *chatterPtr, std::string msg);

using namespace std;

class Server
{

public:
	// CTO(s)
	Server(CommandRcvdHandler /*cmdRcvdHndlr*/);
	Server(const char* /*portNum*/, CommandRcvdHandler /*cmdRcvdHndlr*/);
	Server(UINT /*portNum*/);

	int init();
	void run();
	static int sendMsg(SOCKET /*clientSock*/, std::string /*msg*/);

protected:
	Tuple getClientInfo(SOCKET /*clientSock*/, int /*clientsize*/);
	Chatroom chatroom;
	ChatroomsDB chatroomDB;

private:
	CommandRcvdHandler commandRcvdHandler;
	bool stopped;
	const char *port;
	string ip_address;

#ifdef _WIN32
	WSADATA wsaData;
#endif
	int iResult;
	std::vector<std::shared_ptr<CHATTER>> chatterList;

	struct addrinfo *result = NULL;
	struct addrinfo hints;
	struct sockaddr_in client;

	SOCKET clientSckt;
	SOCKET listenSckt;

	// PRIVATE FUNCTIONS
	// Thread handling functions
	void welcomeChatter(std::shared_ptr<CHATTER> /*chatter*/);
	static int closeClientConnection(SOCKET /*clientSock*/);
	int handleClient(std::shared_ptr<CHATTER> /*chatter*/, DWORD /*tId*/);

	// Socket functions
	SOCKET createSocket();
	int bindSocket();
	int listenSocket();
	int connectSocket();
	int acceptSocket();

	// Exit functions
	bool calledExit(std::string message);
	int handleExit(shared_ptr<CHATTER> c);
};
