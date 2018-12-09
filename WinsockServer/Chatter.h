#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <iostream>
#include <string>
#include <mutex>

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

class CHATTER
{

public:
	CHATTER();
	CHATTER(SOCKET /*socket*/, UINT /*portNum*/, std::string /*name*/);
	~CHATTER();

	SOCKET getSocket();

	UINT getPort();
	std::string getNick();
	std::string getRoom();
	std::string getUsername();
	std::string getPassword();
	void setNick(std::string /*name*/);
	void setUsername(std::string /*name*/);
	void setPassword(std::string /*name*/);
	void setRoom(std::string /*name*/);
	void setOnline(bool);
	void setAdminProperty(bool);
	bool isOnline();
	bool isAdmin();

private:
	SOCKET c_sock;
	UINT port;

	std::string nick;
	std::string password = "";
	std::string username;
	std::string chatRoom;
	bool online = false;
	bool admin = false;
	std::mutex rdMutex;
	std::mutex wrMutex;
};

/*
HOW TO PING FOR REAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv) {
	char *command = NULL;
	char pre[] = "ping -c 1 ";
	char post[] = " >/dev/null 2>&1";
	int ret_code;
	if(argv[1] != NULL) {
		command = (char*)malloc(sizeof(pre)+sizeof(argv[1])+sizeof(post));
		if(command == NULL) {
			fprintf(stderr, "memory allocation failed");
			return -1;
		}
		strcat(command, pre);
		strcat(command, argv[1]);
		strcat(command, post);
		ret_code = system(command);
	}
	else {
		fprintf(stderr, "no host provided");
		return -1;
	}
	fprintf(stdout, "%s returned %i\n", command, ret_code);
	return ret_code;
}
*/
