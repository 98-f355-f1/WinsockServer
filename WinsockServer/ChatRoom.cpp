#include "ChatRoom.h"

Chat::Chatroom::Chatroom()
{
}

Chat::Chatroom::Chatroom(std::string rmName, std::string rmTheme) : roomName(rmName), roomTheme(rmTheme)
{
}

Chat::Chatroom::~Chatroom()
{
}

UINT Chat::Chatroom::getNoChatters()
{
	return vec_chatters.size();
}

std::string Chat::Chatroom::getRoomName()
{
	return roomName;
}

std::string Chat::Chatroom::getRoomTheme()
{
	return roomTheme;
}

void Chat::Chatroom::listChatters()
{
	std::cout << "Current chatters on line: " << std::endl;
	// this section works -EXPERIMENTAL
	for (auto c : vec_chatters)
		std::cout << "\t" << c->getNick() << std::endl;
}