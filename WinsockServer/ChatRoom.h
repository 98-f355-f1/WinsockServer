#pragma once

#include <WS2tcpip.h>
#include <mutex>
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include "Chatter.h"

namespace Chat
{
using namespace std;

	class Chatroom
	{
	public:
		Chatroom();
		Chatroom(string rmName, string rmTheme);
		~Chatroom();

		UINT getNoChatters();
		string getRoomName();
		string getRoomTheme();
		vector<shared_ptr<CHATTER>> vec_chatters;
		void listChatters();

	private:
		string roomName;
		string roomTheme;
		uint32_t no_chatters;

		// private functions

	};
}


/*
class A
{
public:
	static DWORD WINAPI S_Run(LPVOID p)
	{
		return ((A *)p)->Run();
	}

private:
	DWORD Run()
	{
		// now you are in your instance method
	}

	void StartThread()
	{
		DWORD id = 0;
		HANDLE h = CreateThread(NULL, 0, S_Run, this, 0, &id);
		if (h != NULL)
			CloseHandle(h);
	}
};

somewhere in your code
A a;
a.StartThread();

or
HANDLE h = CreateThread(NULL, 0, A::S_Run, (LPVOID)&a, 0, &id);
if (h != NULL)
	CloseHandle(h);
*/