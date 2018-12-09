#pragma once
#include <WS2tcpip.h>
#include "Chatter.h"
#include <unordered_map>

#pragma comment(lib, "WS2_32.lib")

namespace Database
{
	class ChatterDB
	{
		typedef std::unordered_map<SOCKET, std::shared_ptr<CHATTER>> ChattersDB;

	public:
		ChatterDB() {}
		~ChatterDB() {}

		bool insertItem()
		{
			return true;
		}

		// iterator
		std::tuple<SOCKET, CHATTER, std::string> iterator()
		{
			return std::tuple<SOCKET, CHATTER, std::string>();
		}
	};
}
