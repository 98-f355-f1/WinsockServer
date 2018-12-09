#ifndef CHATTER_H
#define CHATTER_H

#include "Client.h"
#include <WS2tcpip.h>
#include <iostream>
#include <map>

class CHATTER {

private:
	SOCKET c_sock;
	int id;
	std::string nick;
	std::string chatRoom;
	bool online = false;
	bool admin = false;

public:
	CHATTER();
	CHATTER(SOCKET socket, std::string name);
	~CHATTER();

	SOCKET getSocket();

	std::string getNick();
	std::string getRoom();
	void setRoom(std::string room);
	void setOnline(bool);
	void setAdminProperty(bool);
	bool isOnline();
	bool isAdmin();
};

#endif // !CHATTER_H

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
