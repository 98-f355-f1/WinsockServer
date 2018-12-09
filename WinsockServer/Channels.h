#pragma once

#include "Server.h"

typedef	std::unordered_map<std::string, int> ChannelsMap;
typedef std::vector<std::string> ChannelsList;

class Channels
{

public:
	Channels();
	Channels(std::string channel);
	~Channels() {}

	void addChannel(std::string channel);
	std::string getChannel(std::string command);
	ChannelsList getChannels();
	ChannelsList channels;

private:
	ChannelsMap channels_m;
	std::string channel;
};
