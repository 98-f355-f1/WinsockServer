#ifndef CLIENT_H // begin CLIENT_H
#define CLIENT_H

#include <WS2tcpip.h>
#include <iostream>
#include <time.h>
#include <cstring>
#include <cstdlib>

#pragma comment(lib, "Ws2_32.lib")

constexpr auto DEFAULT_PORT = "25000";
constexpr auto BUFFER_SIZE = 512;

static char *strcopy(char *dest, const char *src, size_t size);
void getInput(char *dest, int src, int bufSize);

namespace Chat
{
using namespace std;

	class Client
	{
	public:

	private:

	};
}


#endif // !end CLIENT_H
