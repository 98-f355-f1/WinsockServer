#include "Channels.h"
#pragma once

Channels::Channels()
{
}

Channels::Channels(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);
	std::string line;

	if (file.is_open())
	{
		for (int i = 1; getline(file, line); i++)
		{
			channels.push_back(line);
		}
	}
}

void Channels::addChannel(std::string channel)
{
	channels.push_back(channel);
}

std::string Channels::getChannel(std::string channel)
{
	for (auto& c : channels)
		if (c == channel)
			return channel;

	return nullptr;
}

ChannelsList Channels::getChannels()
{
	return channels;
}
