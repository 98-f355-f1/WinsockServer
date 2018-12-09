#include "Chatter.h"

CHATTER::CHATTER()
{
}

CHATTER::CHATTER(SOCKET socket, std::string name) : c_sock(socket), nick(name)
{
}

CHATTER::~CHATTER()
{
}

std::string CHATTER::getNick()
{
	return nick;
}

SOCKET CHATTER::getSocket()
{
	return c_sock;
}

std::string CHATTER::getRoom()
{
	return chatRoom;
}

void CHATTER::setRoom(std::string room)
{
	chatRoom = room;
}

void CHATTER::setOnline(bool t)
{
	online = t;
}

void CHATTER::setAdminProperty(bool t)
{
	admin = t;
}

bool CHATTER::isOnline()
{
	return online;
}

bool CHATTER::isAdmin()
{
	return admin;
}
