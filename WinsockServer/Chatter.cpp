#include "Chatter.h"

CHATTER::CHATTER()
{
}

CHATTER::CHATTER(SOCKET socket, UINT portNum, std::string name) : c_sock(socket), port(portNum), nick(name)
{
}

CHATTER::~CHATTER()
{
}

UINT CHATTER::getPort()
{
	return port;
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

std::string CHATTER::getUsername()
{
	return username;
}

std::string CHATTER::getPassword()
{
	return password;
}

void CHATTER::setNick(std::string nickname)
{
	nick = nickname;
}

void CHATTER::setPassword(std::string passwd)
{
	password = passwd;
}

void CHATTER::setUsername(std::string usrname)
{
	username = usrname;
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
